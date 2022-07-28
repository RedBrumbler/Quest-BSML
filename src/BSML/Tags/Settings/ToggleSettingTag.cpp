#include "BSML/Tags/Settings/ToggleSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/ToggleSetting.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "HMUI/AnimatedSwitchView.hpp"
#include "GlobalNamespace/BoolSettingsController.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ToggleSettingTag> toggleSettingTagParser({"toggle-setting"});
    GameObject* toggleTemplate = nullptr;
    
    void ToggleSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto toggle = go->GetComponent<BSML::ToggleSetting*>();
        SetHostField(host, toggle);
        
        genericSettingData.Apply(toggle->genericSetting, host);
        toggleSettingData.Apply(toggle, host);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* ToggleSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating ToggleSetting");

        if (!toggleTemplate || !Object::IsNativeObjectAlive(toggleTemplate)) {
            auto foundToggle = Resources::FindObjectsOfTypeAll<Toggle*>().FirstOrDefault([](auto x){
                if (!x) return false;
                auto parent = x->get_transform()->get_parent();
                if (!parent) return false;
                return parent->get_gameObject()->get_name() == "Fullscreen";
            });
            toggleTemplate = foundToggle ? foundToggle->get_transform()->get_parent()->get_gameObject() : nullptr;
        }

        auto go = Object::Instantiate(toggleTemplate, parent, false);
        go->SetActive(false);
        auto transform = reinterpret_cast<UnityEngine::RectTransform*>(go->get_transform());
        
        auto nameText = transform->Find("NameText")->get_gameObject();
        auto switchView = transform->Find("SwitchView")->get_gameObject();
        Object::Destroy(go->GetComponent<GlobalNamespace::BoolSettingsController*>());

        go->set_name("BSMLToggle");
        auto toggleSetting = go->AddComponent<ToggleSetting*>();
        HMUI::AnimatedSwitchView* animatedSwitchView = switchView->GetComponent<HMUI::AnimatedSwitchView*>();

        Object::Destroy(nameText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());
        toggleSetting->toggle = switchView->GetComponent<Toggle*>();
        toggleSetting->toggle->onValueChanged = UnityEngine::UI::Toggle::ToggleEvent::New_ctor();
        toggleSetting->toggle->set_interactable(true);
        toggleSetting->toggle->set_isOn(false);
        
        toggleSetting->text = nameText->GetComponent<TMPro::TextMeshProUGUI*>();
        toggleSetting->text->set_text("BSML Toggle");
        toggleSetting->text->set_richText(true);
        toggleSetting->text->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);

        auto layoutElement = go->GetComponent<UnityEngine::UI::LayoutElement*>();
        layoutElement->set_preferredWidth(90.0f);
        go->SetActive(true);

        textMeshProUGUIData.Apply(toggleSetting->text);
        layoutElementData.Apply(layoutElement);
        rectTransformData.Apply(transform);
        return go;
    }

    void ToggleSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing horizontal tag");
        this->::BSML::BSMLTag::parse(elem);

        genericSettingData = GenericSettingData(elem);
        toggleSettingData = ToggleSettingData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        layoutElementData = LayoutElementData(elem);
        rectTransformData = RectTransformData(elem);
    }
}