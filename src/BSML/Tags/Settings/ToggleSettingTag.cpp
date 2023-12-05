#include "BSML/Tags/Settings/ToggleSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/ToggleSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "HMUI/AnimatedSwitchView.hpp"
#include "GlobalNamespace/BoolSettingsController.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ToggleSettingTag> toggleSettingTagParser({"toggle-setting", "bool-setting", "checkbox-setting", "checkbox"});

    GameObject get_toggleTemplate() {
        static SafePtrUnity<GameObject> toggleTemplate;
        if (!toggleTemplate) {
            auto foundToggle = Resources::FindObjectsOfTypeAll<Toggle*>().FirstOrDefault([](auto x){
                if (!x) return false;
                auto parent = x.transform.parent;
                if (!parent) return false;
                return parent.gameObject.name == "Fullscreen";
            });
            toggleTemplate = foundToggle ? foundToggle.transform.parent.gameObject : nullptr;
        }
        return GameObject(toggleTemplate.ptr());
    }

    UnityEngine::GameObject ToggleSettingTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating ToggleSetting");

        auto go = Object::Instantiate(get_toggleTemplate(), parent, false);
        go.SetActive(false);
        UnityEngine::RectTransform transform {go.transform.convert()};

        auto nameText = transform.Find("NameText").gameObject;
        auto switchView = transform.Find("SwitchView").gameObject;
        Object::Destroy(go.GetComponent<GlobalNamespace::BoolSettingsController>());

        go.name = "BSMLToggle";
        auto toggleSetting = go.AddComponent<ToggleSetting>();
        auto animatedSwitchView = switchView.GetComponent<HMUI::AnimatedSwitchView>();

        Object::Destroy(nameText.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());
        toggleSetting.toggle = switchView.GetComponent<Toggle>();
        toggleSetting.toggle.onValueChanged = UnityEngine::UI::Toggle::ToggleEvent::New_ctor();
        toggleSetting.toggle.interactable = true;
        toggleSetting.toggle.isOn = false;

        toggleSetting.text = nameText->GetComponent<TMPro::TextMeshProUGUI>();
        toggleSetting.text.text = "BSML Toggle";
        toggleSetting.text.richText = true;
        toggleSetting.text.overflowMode = TMPro::TextOverflowModes::Ellipsis;

        auto layoutElement = go.GetComponent<LayoutElement>();
        layoutElement.preferredWidth = 90.0f;
        go.SetActive(true);

        auto externalComponents = go.AddComponent<ExternalComponents>();
        externalComponents.Add(toggleSetting.text);

        return go;
    }
}
