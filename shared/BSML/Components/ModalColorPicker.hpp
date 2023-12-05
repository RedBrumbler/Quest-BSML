#pragma once

#include "custom-types/shared/macros.hpp"
#include "ModalView.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/RGBPanelController.hpp"
#include "GlobalNamespace/HSVPanelController.hpp"
#include "GlobalNamespace/ColorChangeUIEventType.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "../GenericSettingWrapper.hpp"

DECLARE_CLASS_CORDL(BSML, ModalColorPicker, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GenericSettingWrapper, genericSetting);
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, host);
        DECLARE_INSTANCE_FIELD(BSML::ModalView, modalView);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::RGBPanelController, rgbPanel);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::HSVPanelController, hsvPanel);
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image, colorImage);
        DECLARE_INSTANCE_FIELD(UnityEngine::Color, _currentColor);

        public:
            std::function<void(UnityEngine::Color)> onChange = nullptr;
            std::function<void(UnityEngine::Color)> done = nullptr;
            std::function<void(void)> cancel = nullptr;
        protected:
            friend class ModalColorPickerData;
            friend class ColorSetting;
            friend class ModalColorPickerHandler;
            /* protected because these are for internal use */
            /* TODO replace with std::function? */
            const MethodInfo* onCancelInfo = nullptr;
            const MethodInfo* onDoneInfo = nullptr;
            const MethodInfo* colorChangeInfo = nullptr;
    );

    FIELD_ACCESSOR(genericSetting);
    FIELD_ACCESSOR(host);
    FIELD_ACCESSOR(modalView);
    FIELD_ACCESSOR(rgbPanel);
    FIELD_ACCESSOR(hsvPanel);
    FIELD_ACCESSOR(colorImage);
    FIELD_ACCESSOR(_currentColor);
    FIELD_ACCESSOR(onChange);
    FIELD_ACCESSOR(done);
    FIELD_ACCESSOR(cancel);
    FIELD_ACCESSOR(onCancelInfo);
    FIELD_ACCESSOR(onDoneInfo);
    FIELD_ACCESSOR(colorChangeInfo);

    DECLARE_INSTANCE_METHOD(UnityEngine::Color, get_currentColor);
    DECLARE_INSTANCE_METHOD(void, set_currentColor, UnityEngine::Color value);
    __declspec(property(get=get_currentColor,put=set_currentColor) UnityEngine::Color currentColor;
    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, CancelPressed);
    DECLARE_INSTANCE_METHOD(void, DonePressed);
    DECLARE_INSTANCE_METHOD(void, OnChange, UnityEngine::Color value, GlobalNamespace::ColorChangeUIEventType type);

    DECLARE_CTOR(ctor);
    protected:
        friend class ModalColorPickerData;
        friend class ColorSetting;
        friend class ModalColorPickerHandler;
)
