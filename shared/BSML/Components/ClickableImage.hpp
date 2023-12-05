#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/EventSystems/IPointerClickHandler.hpp"
#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"
#include "UnityEngine/Color.hpp"

#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "GlobalNamespace/Signal.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
#include "HMUI/ImageView.hpp"

#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"

DECLARE_CLASS_CORDL_INTERFACES(BSML, ClickableImage, HMUI::ImageView, std::vector<Il2CppClass*>({classof(UnityEngine::EventSystems::IPointerClickHandler), classof(UnityEngine::EventSystems::IPointerEnterHandler), classof(UnityEngine::EventSystems::IPointerExitHandler), classof(UnityEngine::EventSystems::IEventSystemHandler)}),
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(GlobalNamespace::Signal, buttonClickedSignal);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::HapticFeedbackController, hapticFeedbackController);
        DECLARE_INSTANCE_FIELD(Libraries::HM::HMLib::VR::HapticPresetSO, hapticFeedbackPresetSO);

        DECLARE_INSTANCE_FIELD(UnityEngine::Color, _highlightColor);
        DECLARE_INSTANCE_FIELD(UnityEngine::Color, _defaultColor);
        DECLARE_INSTANCE_FIELD(bool, _isHighlighted);

        public:
            UnorderedEventCallback<> onClick;
            std::function<void()> onEnter;
            std::function<void()> onExit;
    );

    FIELD_ACCESSOR(buttonClickedSignal);
    FIELD_ACCESSOR(hapticFeedbackController);
    FIELD_ACCESSOR(hapticFeedbackPresetSO);
    FIELD_ACCESSOR(_highlightColor);
    FIELD_ACCESSOR(_defaultColor);
    FIELD_ACCESSOR(_isHighlighted);
    FIELD_ACCESSOR(onClick);
    FIELD_ACCESSOR(onEnter);
    FIELD_ACCESSOR(onExit);

    DECLARE_INSTANCE_METHOD(void, set_highlightColor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(UnityEngine::Color, get_highlightColor);
    __declspec(property(get=get_highlightColor, put=set_highlightColor)) UnityEngine::Color highlightColor;
    DECLARE_INSTANCE_METHOD(void, set_defaultColor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(UnityEngine::Color, get_defaultColor);
    __declspec(property(get=get_defaultColor, put=set_defaultColor)) UnityEngine::Color defaultColor;
    DECLARE_INSTANCE_METHOD(void, UpdateHighlight);
    DECLARE_INSTANCE_METHOD(bool, get_isHighlighted);
    DECLARE_INSTANCE_METHOD(void, set_isHighlighted, bool value);
    __declspec(property(get=get_isHighlighted, put=set_isHighlighted)) bool isHighlighted;
    DECLARE_INSTANCE_METHOD(void, Vibrate, bool left);

    DECLARE_OVERRIDE_METHOD(void, OnPointerClick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerClickHandler::OnPointerClick>::get(), UnityEngine::EventSystems::PointerEventData eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get(), UnityEngine::EventSystems::PointerEventData eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get(), UnityEngine::EventSystems::PointerEventData eventData);


    DECLARE_CTOR(ctor);

)
