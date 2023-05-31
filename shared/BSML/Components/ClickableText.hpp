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
#include "HMUI/CurvedTextMeshPro.hpp"

#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(BSML, ClickableText, HMUI::CurvedTextMeshPro, std::vector<Il2CppClass*>({classof(UnityEngine::EventSystems::IPointerClickHandler*), classof(UnityEngine::EventSystems::IPointerEnterHandler*), classof(UnityEngine::EventSystems::IPointerExitHandler*), classof(UnityEngine::EventSystems::IEventSystemHandler*)}),
    DECLARE_INSTANCE_METHOD(void, set_highlightColor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(UnityEngine::Color, get_highlightColor);
    DECLARE_INSTANCE_METHOD(void, set_defaultColor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(UnityEngine::Color, get_defaultColor);
    DECLARE_INSTANCE_METHOD(void, UpdateHighlight);
    DECLARE_INSTANCE_METHOD(bool, get_isHighlighted);
    DECLARE_INSTANCE_METHOD(void, set_isHighlighted, bool value);
    DECLARE_INSTANCE_METHOD(void, Vibrate, bool left);

    DECLARE_OVERRIDE_METHOD(void, OnPointerClick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerClickHandler::OnPointerClick>::get(), UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get(), UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get(), UnityEngine::EventSystems::PointerEventData* eventData);

    /* purely here because CurvedTextMeshPro is larger than it says it is */
    DECLARE_INSTANCE_FIELD(void*, padding1);
    DECLARE_INSTANCE_FIELD(void*, padding2);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::Signal*, buttonClickedSignal);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::HapticFeedbackController*, hapticFeedbackController);
    DECLARE_INSTANCE_FIELD(Libraries::HM::HMLib::VR::HapticPresetSO*, hapticFeedbackPresetSO);

    DECLARE_INSTANCE_FIELD(UnityEngine::Color, highlightColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, defaultColor);
    DECLARE_INSTANCE_FIELD(bool, isHighlighted);

    DECLARE_CTOR(ctor);

    public:
        UnorderedEventCallback<> onClick;
        std::function<void()> onEnter;
        std::function<void()> onExit;

)
