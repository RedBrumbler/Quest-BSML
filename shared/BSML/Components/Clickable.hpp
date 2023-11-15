#pragma once

#include "custom-types/shared/macros.hpp"

#include "HMUI/Touchable.hpp"
#include "UnityEngine/EventSystems/IPointerClickHandler.hpp"
#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"

#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "GlobalNamespace/Signal.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(BSML, Clickable, HMUI::Touchable, std::vector<Il2CppClass*>({classof(UnityEngine::EventSystems::IPointerClickHandler*), classof(UnityEngine::EventSystems::IPointerEnterHandler*), classof(UnityEngine::EventSystems::IPointerExitHandler*), classof(UnityEngine::EventSystems::IEventSystemHandler*)}),

    DECLARE_INSTANCE_FIELD(GlobalNamespace::Signal*, buttonClickedSignal);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::HapticFeedbackController*, hapticFeedbackController);
    DECLARE_INSTANCE_FIELD(Libraries::HM::HMLib::VR::HapticPresetSO*, hapticFeedbackPresetSO);

    DECLARE_OVERRIDE_METHOD(void, OnPointerClick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerClickHandler::OnPointerClick>::get(), UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get(), UnityEngine::EventSystems::PointerEventData* eventData);
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get(), UnityEngine::EventSystems::PointerEventData* eventData);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Vibrate, bool left);
    DECLARE_CTOR(ctor);

    public:
        UnorderedEventCallback<> onClick;
        UnorderedEventCallback<> onEnter;
        UnorderedEventCallback<> onExit;

)
