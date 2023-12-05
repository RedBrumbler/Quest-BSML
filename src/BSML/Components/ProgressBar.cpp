#include "BSML/Components/ProgressBar.hpp"
#include "Helpers/creation.hpp"
#include "Helpers/utilities.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/WaitForSecondsRealtime.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/RenderMode.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"

// type borrowed from https://github.com/darknight1050/QuestUI
DEFINE_TYPE(BSML, ProgressBar);

namespace BSML {
    void ProgressBar::OnDisable() {
        if (!inited) return;
        loadingBar.fillAmount = 0;
    }

    void ProgressBar::Awake() {
        inited = false;
        showingMessage = false;
    }

    void ProgressBar::Update() {
        if (!canvas || !canvas.m_CachedPtr || !canvas.enabled) return;
        float pong = UnityEngine::Time::get_time() * 0.35f;

        float graph = std::fmod(pong, 2);
        if (graph > 1) graph = (2 - graph);
        auto color = UnityEngine::Color::HSVToRGB(graph, 1, 1);
        loadingBar.color = color;
        headerText.color = color;
    }

    custom_types::Helpers::Coroutine ProgressBar::DisableCanvasRoutine(float time) {
        static constexpr const float increment = 0.2f;

        float accumulation = 0.0f;
        while (accumulation < time) {
            SetProgress(accumulation / time);
            co_yield System::Collections::IEnumerator(UnityEngine::WaitForSecondsRealtime::New_ctor(increment));
            accumulation += increment;
        }

        gameObject.SetActive(false);
        showingMessage = false;

        co_return;
    }

    void ProgressBar::ShowMessage(StringW text, float time) {
        ShowMessage(text);

        StopAllCoroutines();
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(DisableCanvasRoutine(time)));
    }

    void ProgressBar::ShowMessage(StringW text) {
        if (!inited) return;
        showingMessage = true;
        headerText.text = text;
        gameObject.SetActive(true);
    }

    void ProgressBar::SetProgress(float progress) {
        if (!inited) return;
        loadingBar.fillAmount = std::clamp(progress, 0.0f, 1.0f);
        if (!gameObject.active) gameObject.SetActive(true);
    }

    void ProgressBar::SetProgress(float progress, bool showBar) {
        if (!inited) return;
        loadingBar.fillAmount = std::clamp(progress, 0.0f, 1.0f);
        gameObject.SetActive(showBar);
    }

    ProgressBar* ProgressBar::CreateProgressBar(UnityEngine::Vector3 position, UnityEngine::Vector3 scale, UnityEngine::Vector3 rotation, StringW mainText, StringW subText1, StringW subText2) {
        auto bar = UnityEngine::GameObject::New_ctor("LoadingStatus").AddComponent<ProgressBar>();
        auto barGameObject = bar.gameObject;
        auto barObjectTransform = bar.transform;
        barObjectTransform.position = position;
        barObjectTransform.eulerAngles = rotation;
        barObjectTransform.localScale = scale / 100;

        bar.canvas = barGameObject.AddComponent<UnityEngine::Canvas>();
        bar.canvas.renderMode = UnityEngine::RenderMode::WorldSpace;
        barGameObject.AddComponent<HMUI::CurvedCanvasSettings>().SetRadius(0.0f);

        auto ct = bar.canvas.transform;
        ct.position = position;
        ct.localScale = scale / 100;

        UnityEngine::Vector2 LoadingBarSize = {100, 10};
        UnityEngine::Color BackgroundColor = {0, 0, 0, 0.2f};
        UnityEngine::RectTransform rectTransform {ct.convert()};
        rectTransform.sizeDelta = {200, 50};

        // why set everything after creating it in the first place ?
        bar.subText2 = Helpers::CreateText(ct, subText2, {10, 31}, {100, 20});
        bar.subText2.fontSize = 7.0f;
        bar.subText1 = Helpers::CreateText(ct, subText1, {10, 23}, {100, 20});
        bar.subText1.fontSize = 9.0f;
        bar.headerText = Helpers::CreateText(ct, mainText,{10, 15}, {100, 20});
        bar.headerText.fontSize = 15.0f;

        bar.loadingBackground = UnityEngine::GameObject::New_ctor("Background").AddComponent<UnityEngine::UI::Image>();
        UnityEngine::RectTransform rectTransform {bar.loadingBackground.transform.convert()};
        rectTransform.SetParent(ct, false);
        rectTransform.sizeDelta = LoadingBarSize;
        bar.loadingBackground.color = BackgroundColor;

        bar.loadingBar = UnityEngine::GameObject::New_ctor("Loading Bar").AddComponent<UnityEngine::UI::Image>();
        rectTransform = UnityEngine::RectTransform{bar.loadingBar.transform.convert()};
        rectTransform.SetParent(ct, false);
        rectTransform.sizeDelta = LoadingBarSize;

        bar.loadingBar.sprite = BSML::Utilities::ImageResources::GetWhitePixel();
        bar.loadingBar.type = UnityEngine::UI::Image::Type::Filled;
        bar.loadingBar.fillMethod = UnityEngine::UI::Image::FillMethod::Horizontal;
        bar.loadingBar.color = {1.0f, 1.0f, 1.0f, 0.5f};

        UnityEngine::Object::DontDestroyOnLoad(bar.gameObject);
        bar.inited = true;
        return bar;
    }
}
