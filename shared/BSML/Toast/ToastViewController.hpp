#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/CanvasGroup.hpp"
#include "UnityEngine/Coroutine.hpp"

#include "Toast.hpp"
#include "../FloatingScreen/FloatingScreen.hpp"
#include "../Components/Clickable.hpp"
#include <queue>
#include <mutex>

DECLARE_CLASS_CODEGEN(BSML, ToastViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(BSML::FloatingScreen*, screen);
    DECLARE_INSTANCE_FIELD(UnityEngine::Coroutine*, displayRoutine);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, OnApplicationFocus, bool hasFocus);
    DECLARE_INSTANCE_METHOD(void, OnApplicationPause, bool pauseStatus);

    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Vector2, originalPosition);
    DECLARE_INSTANCE_FIELD_PRIVATE(BSML::Clickable*, clickable);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::CanvasGroup*, toastGroup);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::GameObject*, root);
    DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ImageView*, accent);
    DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ImageView*, image);
    DECLARE_INSTANCE_FIELD_PRIVATE(TMPro::TextMeshProUGUI*, title);
    DECLARE_INSTANCE_FIELD_PRIVATE(TMPro::TextMeshProUGUI*, subtext);
    DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::ImageView*, progressBar);

    DECLARE_CTOR(ctor);

public:
    float animationSpeed = 5.0f;
    void Enqueue(const BSML::Toast& toast);
    static ToastViewController* get_instance();
    static ToastViewController* instance;

private:
    std::mutex queueMutex;
    std::queue<BSML::Toast> toastQueue;

    enum ToastingPhase {
        Hidden,
        Appearing,
        Display,
        Disappearing
    };

    ToastingPhase phase = Hidden;
    bool wasClicked = false, initialized = false, pointerOnToast = false, isPaused = false;

    custom_types::Helpers::Coroutine NextToastRoutine();
    void GameRestart();
    void Clicked();
    void Enter();
    void Exit();
)
