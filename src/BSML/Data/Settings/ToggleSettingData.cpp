#include "BSML/Data/Settings/ToggleSettingData.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"

namespace BSML {
    ToggleSettingData::ToggleSettingData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("on-text", onText);
        GET_BSML_STRING("on-label", onText);
        GET_BSML_STRING("off-text", offText);
        GET_BSML_STRING("off-label", offText);
    }

    void ToggleSettingData::Apply(BSML::ToggleSetting* toggleSetting, Il2CppObject* host) const {
        if (!toggleSetting || !host) {
            ERROR("nullptr passed to ToggleSettingData::Apply");
            return;
        }

        auto transform = toggleSetting->toggle->get_transform();
        if (get_onText().has_value()) {
            auto onTextObject = transform->Find("BackgroundImage/OnText")->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            onTextObject->set_text(get_onText().value());
        }

        if (get_offText().has_value()) {
            auto offTextObject = transform->Find("BackgroundImage/OffText")->get_gameObject()->GetComponent<TMPro::TextMeshProUGUI*>();
            offTextObject->set_text(get_offText().value());
        }
    }
}