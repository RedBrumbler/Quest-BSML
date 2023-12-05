#include "BSML/FloatingScreen/FloatingScreen.hpp"
#include "BSML/FloatingScreen/FloatingScreenHandle.hpp"
#include "Helpers/creation.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/AdditionalCanvasShaderChannels.hpp"
#include "UnityEngine/UI/CanvasScaler.hpp"
#include "UnityEngine/UI/RectMask2D.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

#include "VRPointerEnabledPatch.hpp"

DEFINE_TYPE(BSML, FloatingScreen);

static inline UnityEngine::AdditionalCanvasShaderChannels operator |(UnityEngine::AdditionalCanvasShaderChannels a, UnityEngine::AdditionalCanvasShaderChannels b) {
    return a | b;
}
namespace BSML {
    SafePtrUnity<UnityEngine::Material> FloatingScreen::_fogMaterial;
    FloatingScreen FloatingScreen::CreateFloatingScreen(UnityEngine::Vector2 screenSize, bool createHandle, UnityEngine::Vector3 position, UnityEngine::Quaternion rotation, float curvatureRadius, bool hasBackground) {
        auto components = ArrayW<System::Type>(static_cast<il2cpp_array_size_t>(5));
        components[0] = csTypeOf(BSML::FloatingScreen);
        components[1] = csTypeOf(UnityEngine::UI::CanvasScaler);
        components[2] = csTypeOf(UnityEngine::UI::RectMask2D);
        components[3] = csTypeOf(VRUIControls::VRGraphicRaycaster);
        components[4] = csTypeOf(HMUI::CurvedCanvasSettings);

        auto screen = UnityEngine::GameObject::New_ctor("BSMLFloatingScreen", components).GetComponent<FloatingScreen>();
        screen.GetComponent<VRUIControls::VRGraphicRaycaster>().physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();

        auto curvedCanvasSettings = screen.GetComponent<HMUI::CurvedCanvasSettings>();
        curvedCanvasSettings.SetRadius(curvatureRadius);

        auto canvas = screen.GetComponent<UnityEngine::Canvas>();
        canvas.additionalShaderChannels = UnityEngine::AdditionalCanvasShaderChannels::TexCoord1 | UnityEngine::AdditionalCanvasShaderChannels::TexCoord2;
        canvas.sortingOrder = 4;

        auto scaler = screen.GetComponent<UnityEngine::UI::CanvasScaler>();
        scaler.dynamicPixelsPerUnit = 3.44f;
        scaler.referencePixelsPerUnit = 10.0f;

        if (hasBackground)
        {
            auto components = ArrayW<System::Type>(static_cast<il2cpp_array_size_t>(2));
            components[0] = csTypeOf(UnityEngine::RectTransform);
            components[1] = csTypeOf(HMUI::ImageView);

            auto backGroundGo = UnityEngine::GameObject::New_ctor("bg", components);
            backGroundGo.transform.SetParent(canvas.transform, false);
            auto rectTransform = backGroundGo.GetComponent<UnityEngine::RectTransform>();
            rectTransform.sizeDelta = screenSize;
            rectTransform.anchorMin = {0, 0};
            rectTransform.anchorMax = {1, 1};
            rectTransform.offsetMin = {0, 0};
            rectTransform.offsetMax = {0, 0};

            auto background = backGroundGo.GetComponent<HMUI::ImageView>();
            background.sprite = ::BSML::Utilities::FindSpriteCached("MainScreenMask");
            background.type = UnityEngine::UI::Image::Type::Sliced;
            background.color = {0.7450981f, 0.7450981f, 0.7450981f, 1.0f};
            if (!_fogMaterial)
                _fogMaterial = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material>().FirstOrDefault([](auto x){ return x.name == "UIFogBG"; });
            background.material = _fogMaterial.ptr();
            background.preserveAspect = true;
        }

        auto screenTransform = screen.transform;
        screenTransform.position = position;
        screenTransform.rotation = rotation;
        screenTransform.localScale = {0.02f, 0.02f, 0.02f};

        screen.ScreenSize = screenSize;
        screen.ShowHandle = createHandle;

        screen.gameObject.layer = 5;

        return screen;
    }

    FloatingScreen FloatingScreen::CreateFloatingScreenWithViewcontroller(Il2CppReflectionType* vcType, UnityEngine::Vector2 screenSize, bool createHandle, UnityEngine::Vector3 position, UnityEngine::Quaternion rotation, float curvatureRadius, bool hasBackground) {
        auto scr = CreateFloatingScreen(screenSize, createHandle, position, rotation, curvatureRadius, hasBackground);
        auto vc = BSML::Helpers::CreateViewController(System::Type(vcType));
        scr.SetRootViewController(vc, HMUI::ViewController::AnimationType::In);
        return scr;
    }

    void FloatingScreen::OnPointerCreated(VRUIControls::VRPointer pointer) {
        CreateHandle(pointer);
    }

    void FloatingScreen::CreateHandle(VRUIControls::VRPointer pointer) {
        if (!pointer || !pointer.m_CachedPtr) {
            pointer = UnityEngine::Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer>().FirstOrDefault();
        }

        if (pointer && pointer.m_CachedPtr) {
            bool pointerChanged = !(screenMover && screenMover.m_CachedPtr) || screenMover.gameObject != pointer.gameObject;

            if (pointerChanged) {
                if (screenMover && screenMover.m_CachedPtr) UnityEngine::Object::Destroy(screenMover);
                screenMover = pointer.gameObject.AddComponent<FloatingScreenMoverPointer>();
            }

            if (!(handle && handle->m_CachedPtr)) {
                handle = UnityEngine::GameObject::CreatePrimitive(UnityEngine::PrimitiveType::Cube);
                handle.transform.SetParent(transform);
                handle.transform.localRotation = UnityEngine::Quaternion::get_identity();
                UpdateHandle();
                handle.AddComponent<FloatingScreenHandle>().enabled = false;
            }

            if (pointerChanged) screenMover.Init(this);
        } else {
            ERROR("Failed to get VR pointer, handle was not created!");
        }
    }

    void FloatingScreen::OnHandleGrab(VRUIControls::VRPointer pointer) {
        if (HandleGrabbed.size() > 0) HandleGrabbed.invoke(*this, FloatingScreenHandleEventArgs(pointer, transform.position, transform.rotation));
    }

    void FloatingScreen::OnHandleReleased(VRUIControls::VRPointer pointer) {
        if (HandleReleased.size() > 0) HandleReleased.invoke(*this, FloatingScreenHandleEventArgs(pointer, transform.position, transform.rotation));
    }

    void FloatingScreen::UpdateHandle() {
        if (!handle || !handle->m_CachedPtr.m_value) return;
        auto screenSize = get_ScreenSize();
        switch (get_HandleSide())
        {
            case Side::Left:
                handle.transform.localPosition = {-screenSize.x / 2.0f, 0.0f, 0.0f};
                handle.transform.localScale = {screenSize.x / 15.0f, screenSize.y * 0.8f, screenSize.x / 15.0f};
                break;
            case Side::Right:
                handle.transform.localPosition = {screenSize.x / 2.0f, 0.0f, 0.0f};
                handle.transform.localScale = {screenSize.x / 15.0f, screenSize.y * 0.8f, screenSize.x / 15.0f};
                break;
            case Side::Top:
                handle.transform.localPosition = {0.0f, screenSize.y / 2.0f, 0.0f};
                handle.transform.localScale = {screenSize.x * 0.8f, screenSize.y / 15.0f, screenSize.y / 15.0f};
                break;
            case Side::Bottom:
                handle.transform.localPosition = {0.0f, -screenSize.y / 2.0f, 0.0f};
                handle.transform.localScale = {screenSize.x * 0.8f, screenSize.y / 15.0f, screenSize.y / 15.0f};
                break;
            case Side::Full:
                handle.transform.localPosition = {};
                handle.transform.localScale = {screenSize.x, screenSize.y, screenSize.x / 15.0f};
                break;
        }

        handle.GetComponent<UnityEngine::MeshRenderer>().enabled = HandleSide != Side::Full;
    }

    void FloatingScreen::OnDestroy() {
        isBeingDestroyed = true;
        VRPointerEnabledPatch::OnPointerEnabled -= {&FloatingScreen::OnPointerCreated, this};
    }


    UnityEngine::RectTransform FloatingScreen::get_rectTransform() {
        return RectTransform(transform.convert());
    }

    UnityEngine::Vector2 FloatingScreen::get_ScreenSize() {
        return rectTransform.sizeDelta;
    }

    void FloatingScreen::set_ScreenSize(UnityEngine::Vector2 value) {
        rectTransform.sizeDelta = value;
        UpdateHandle();
    }

    UnityEngine::Vector3 FloatingScreen::get_ScreenPosition() {
        return transform.position;
    }

    void FloatingScreen::set_ScreenPosition(UnityEngine::Vector3 value) {
        transform.position = value;
    }

    UnityEngine::Quaternion FloatingScreen::get_ScreenRotation() {
        return transform.rotation;
    }

    void FloatingScreen::set_ScreenRotation(UnityEngine::Quaternion value) {
        transform.rotation = value;
    }

    bool FloatingScreen::get_ShowHandle() {
        return _showHandle;
    }

    void FloatingScreen::set_ShowHandle(bool value) {
        _showHandle = value;
        if (_showHandle) {
            if (!handle || !handle->m_CachedPtr.m_value) CreateHandle();
            else handle->SetActive(true);

            VRPointerEnabledPatch::OnPointerEnabled -= {&FloatingScreen::OnPointerCreated, this};
            VRPointerEnabledPatch::OnPointerEnabled += {&FloatingScreen::OnPointerCreated, this};
        } else if (!_showHandle && handle && handle.m_CachedPtr) {
            handle.SetActive(false);
            VRPointerEnabledPatch::OnPointerEnabled -= {&FloatingScreen::OnPointerCreated, this};
        }
    }

    bool FloatingScreen::get_HighlightHandle() {
        return _highlightHandle;
    }

    void FloatingScreen::set_HighlightHandle(bool value) {
        _highlightHandle = value;
        if (_highlightHandle) {
            if (!get_ShowHandle()) {
                set_ShowHandle(true);
            }

            handle.GetComponent<FloatingScreenHandle>().enabled = true;
        } else {
            if (handle && handle->m_CachedPtr)
                handle.GetComponent<FloatingScreenHandle>().enabled = false;
        }
    }

    Side FloatingScreen::get_HandleSide() {
        return _handleSide;
    }

    void FloatingScreen::set_HandleSide(Side value) {
        _handleSide = value;
        UpdateHandle();
    }

}
