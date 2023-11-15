#include "BSML/Toast/ToastViewController.hpp"
#include "BSML/FloatingScreen/FloatingScreen.hpp"
#include "BSML.hpp"

#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"

#include "logging.hpp"
#include "assets.hpp"

DEFINE_TYPE(BSML, ToastViewController);

#define coro(coroutine) GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(coroutine))
#define stop_coro(coroutine) GlobalNamespace::SharedCoroutineStarter::get_instance()->StopCoroutine(coroutine)

namespace BSML {
    ToastViewController* ToastViewController::instance = nullptr;
    ToastViewController* ToastViewController::get_instance() {
        if (instance && instance->m_CachedPtr.m_value) return instance;
        INFO("Creating new instance of ToastViewController");
        auto screen = FloatingScreen::CreateFloatingScreenWithViewcontroller<ToastViewController*>({90, 45}, false, {0, 3, 5}, {}, 0, false);
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
        clickable->onEnter -= {&ToastViewController::Enter, this};
        clickable->onExit -= {&ToastViewController::Exit, this};
    }

    void ToastViewController::GameRestart() {
        if (displayRoutine) {
            stop_coro(displayRoutine);
            displayRoutine = nullptr;
        }
        Object::Destroy(get_gameObject());
    }

    void ToastViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) BSML::parse_and_construct(IncludedAssets::ToastView_bsml, get_transform(), this);
    }

    void ToastViewController::PostParse() {
        toastGroup = root->AddComponent<UnityEngine::CanvasGroup*>();
        toastGroup->set_alpha(0);

        originalPosition = reinterpret_cast<UnityEngine::RectTransform*>(root->get_transform())->get_anchoredPosition();

        clickable = root->AddComponent<BSML::Clickable*>();
        clickable->onClick += {&ToastViewController::Clicked, this};
        clickable->onEnter += {&ToastViewController::Enter, this};
        clickable->onExit += {&ToastViewController::Exit, this};

        accent->set_type(UnityEngine::UI::Image::Type::Filled);

        progressBar->set_type(UnityEngine::UI::Image::Type::Filled);
        progressBar->set_fillMethod(UnityEngine::UI::Image::FillMethod::Horizontal);
        progressBar->set_color({1, 1, 1, 0.5f});

        initialized = true;
    }

    custom_types::Helpers::Coroutine ToastViewController::NextToastRoutine() {
        if (toastQueue.empty()) co_return;
        auto& toast = toastQueue.front();
        // should probably do better guarding here tbh, but due to how routines are sequential you wouldn't actually get any sort of race conditions :copium:
        while (phase != Hidden) co_yield nullptr;

        phase = Appearing;
        DEBUG("Phase switch to appearing");

        INFO("clickable:    {}", fmt::ptr(clickable));
        INFO("toastGroup:   {}", fmt::ptr(toastGroup));
        INFO("root:         {}", fmt::ptr(root));
        INFO("accent:       {}", fmt::ptr(accent));
        INFO("image:        {}", fmt::ptr(image));
        INFO("title:        {}", fmt::ptr(title));
        INFO("subtext:      {}", fmt::ptr(subtext));
        INFO("progressBar:  {}", fmt::ptr(progressBar));

        auto t = reinterpret_cast<UnityEngine::RectTransform*>(root->get_transform());
        auto original_position = t->get_anchoredPosition();
        // setup internal toast view to have correct text
        root->SetActive(false);
        title->set_text(toast.title);

        subtext->get_gameObject()->SetActive(!toast.subtext.empty());
        subtext->set_text(toast.subtext);
        if (toast.imageSetup) {
            toast.imageSetup->apply(image);
        } else {
            // TODO: clear image or set default
            image->set_sprite(nullptr);
        }
        toast.accentColor.a = 1.0f;
        accent->set_color(toast.accentColor);

        toastGroup->set_alpha(0);
        progressBar->set_fillAmount(0.0f);

        root->SetActive(true);

        // make the toast move and appear at the same time over some frames
        auto target_position = t->get_anchoredPosition();
        for (float y = target_position.y - 5; y < target_position.y; y += animationSpeed * UnityEngine::Time::get_deltaTime()) {
            t->set_anchoredPosition({target_position.x, y});
            toastGroup->set_alpha(1 - ((target_position.y - y) / 5.0f));
            if (wasClicked) { // if clicked, invoke callback
                if (toast.onClick != nullptr) toast.onClick();
                toast.onClick = nullptr;
            }
            co_yield nullptr;
        }
        t->set_anchoredPosition(target_position);
        toastGroup->set_alpha(1);

        phase = Display;
        DEBUG("Phase switch to display");
        // wait an amount of time as given in toast, showing progress through filling the progress bar image
        for (float t = toast.displayTime; t >= 0; t -= UnityEngine::Time::get_deltaTime()) {
            float progress = t / toast.displayTime;
            progressBar->set_fillAmount(1 - std::clamp(progress, 0.0f, 1.0f));

            while(pointerOnToast) { // while hovering, freeze the countdown
                if (wasClicked) { // if clicked, execute the onclick here
                    progressBar->set_fillAmount(1.0f);
                    if (toast.onClick != nullptr) toast.onClick();
                    toast.onClick = nullptr;
                }
                co_yield nullptr;
            }

            if (wasClicked) { // if clicked, end the display time and start hiding
                progressBar->set_fillAmount(1.0f);
                if (toast.onClick != nullptr) toast.onClick();
                toast.onClick = nullptr;
                break;
            }
            co_yield nullptr;
        }

        phase = Disappearing;
        DEBUG("Phase switch to disappearing");
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

        // setup for next toast
        phase = Hidden;
        wasClicked = false;
        delete toast.imageSetup;
        toastQueue.pop();
        displayRoutine = nullptr;
        co_return;
    }

    void ToastViewController::Update() {
        // if we have toasts to display, aren't displaying one right now, and are ready to display
        if (!toastQueue.empty() && !displayRoutine && initialized) {
            std::lock_guard<std::mutex> lock(queueMutex);
            INFO("popping from queue of length: {}", toastQueue.size());
            displayRoutine = coro(NextToastRoutine());
        }
    }

    void ToastViewController::Enqueue(const BSML::Toast& toast) {
        std::lock_guard<std::mutex> lock(queueMutex);
        toastQueue.push(toast);
    }

    void ToastViewController::Clicked() {
        if (phase == Hidden) return;
        if (wasClicked) return;

        wasClicked = true;
    }

    void ToastViewController::Enter() {
        pointerOnToast = true;
    }

    void ToastViewController::Exit() {
        pointerOnToast = false;
    }
}