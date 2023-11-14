#include "BSML/Toast/ToastViewController.hpp"
#include "BSML/FloatingScreen/FloatingScreen.hpp"
#include "BSML.hpp"

#include "UnityEngine/Time.hpp"

#include "logging.hpp"
#include "assets.hpp"

DEFINE_TYPE(BSML, ToastViewController);

namespace BSML {
    ToastViewController* ToastViewController::instance = nullptr;
    ToastViewController* ToastViewController::get_instance() {
        if (instance && instance->m_CachedPtr.m_value) return instance;
        auto screen = FloatingScreen::CreateFloatingScreenWithViewcontroller<ToastViewController*>({90, 40}, false, {0, 5, 10}, {}, 0, true);
        UnityEngine::Object::DontDestroyOnLoad(screen->get_gameObject());

        instance = reinterpret_cast<ToastViewController*>(screen->rootViewController);
        instance->screen = screen;
        return instance;
    }

    void ToastViewController::ctor() {
        INVOKE_CTOR();
        INVOKE_BASE_CTOR(classof(HMUI::ViewController*));

        BSML::Events::onGameDidRestart += {&ToastViewController::GameRestart, this};
    }

    void ToastViewController::OnDestroy() {
        BSML::Events::onGameDidRestart -= {&ToastViewController::GameRestart, this};
        clickable->onClick -= {&ToastViewController::Clicked, this};
    }

    void ToastViewController::GameRestart() {
        StopAllCoroutines();
        Object::Destroy(get_gameObject());
    }

    void ToastViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) BSML::parse_and_construct(IncludedAssets::ToastView_bsml, get_transform(), this);
    }

    void ToastViewController::PostParse() {
        toastGroup = root->AddComponent<UnityEngine::CanvasGroup*>();
        toastGroup->set_alpha(0);

        clickable = root->AddComponent<BSML::Clickable*>();
        clickable->onClick += {&ToastViewController::Clicked, this};

        progressBar->set_type(UnityEngine::UI::Image::Type::Filled);
        progressBar->set_fillMethod(UnityEngine::UI::Image::FillMethod::Horizontal);
        progressBar->set_color({1, 1, 1, 0.5f});
    }

    custom_types::Helpers::Coroutine ToastViewController::ToastRoutine(Toast toast) {
        // should probably do better guarding here tbh, but due to how routines are sequential you wouldn't actually get any sort of race conditions :copium:
        while (phase != Hidden) co_yield nullptr;

        phase = Appearing;
        auto t = reinterpret_cast<UnityEngine::RectTransform*>(root->get_transform());
        auto original_position = t->get_anchoredPosition();

        // setup internal toast view to have correct text
        root->SetActive(false);
        title->set_text(toast.title);

        text->get_gameObject()->SetActive(!toast.subtext.empty());
        title->set_text(toast.subtext);
        image->set_sprite(toast.image);

        toastGroup->set_alpha(0);
        root->SetActive(true);

        // make the toast move and appear at the same time over some frames
        auto target_position = t->get_anchoredPosition();
        for (float y = target_position.y - 5; y < target_position.y; y += animationSpeed * UnityEngine::Time::get_deltaTime()) {
            t->set_anchoredPosition({target_position.x, y});
            toastGroup->set_alpha((target_position.y - y) / 5.0f);
            if (wasClicked) { // if clicked, invoke callback
                if (toast.onClick != nullptr) toast.onClick();
                toast.onClick = nullptr;
            }
            co_yield nullptr;
        }
        t->set_anchoredPosition(target_position);
        toastGroup->set_alpha(1);

        phase = Display;
        // wait an amount of time as given in toast, showing progress through filling the progress bar image
        for (float t = toast.displayTime; t >= 0; t -= UnityEngine::Time::get_deltaTime()) {
            float progress = t / toast.displayTime;
            progressBar->set_fillAmount(std::clamp(progress, 0.0f, 1.0f));

            if (wasClicked) { // if clicked, end the display time and start hiding
                progressBar->set_fillAmount(1.0f);
                if (toast.onClick != nullptr) toast.onClick();
                toast.onClick = nullptr;
                break;
            }
            co_yield nullptr;
        }

        phase = Disappearing;
        // make the toast move back down and disappear
        target_position.y -= 5;
        for (float y = target_position.y + 5; y > target_position.y; y -= animationSpeed * UnityEngine::Time::get_deltaTime()) {
            t->set_anchoredPosition({target_position.x, y});
            toastGroup->set_alpha((y - target_position.y) / 5.0f);
            if (wasClicked) { // if clicked while disappearing, still execute the onclick
                if (toast.onClick != nullptr) toast.onClick();
                toast.onClick = nullptr;
            }
            co_yield nullptr;
        }

        // restore original position
        toastGroup->set_alpha(0);
        t->set_anchoredPosition(original_position);
        phase = Hidden;
        co_return;
    }

    void ToastViewController::Update() {
        if (phase == Hidden) {
            std::lock_guard<std::mutex> lock(queueMutex);
            StartCoroutine(custom_types::Helpers::CoroutineHelper::New(ToastRoutine(toastQueue.front())));
            toastQueue.pop();
        }
    }

    void ToastViewController::Enqueue(const BSML::Toast& toast) {
        std::lock_guard<std::mutex> lock(queueMutex);
        toastQueue.push(toast);
    }

    void ToastViewController::Clicked() {
        if (phase != Display) return;
        if (wasClicked) return;

        wasClicked = true;
    }
}
