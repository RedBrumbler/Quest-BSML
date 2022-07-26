#include "BSML/Tags/Settings/IncDecSettingTag.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "GlobalNamespace/FormattedFloatListSettingsValueController.hpp"
#include "UnityEngine/UI/Button.hpp"

GlobalNamespace::FormattedFloatListSettingsValueController* valueControllerTemplate = nullptr;

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    void IncDecSettingTagBase::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto incrementSetting = go->GetComponent<BSML::IncDecSetting*>();
        genericSettingData.Apply(incrementSetting->genericSetting, host);
        SetHostField(host, incrementSetting);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* IncDecSettingTagBase::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating IncDecSetting");
        if (!valueControllerTemplate || !Object::IsNativeObjectAlive(valueControllerTemplate)) {
            valueControllerTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController*>().First([](auto x){ return x->get_name() == "VRRenderingScale";});
        }

        auto baseSetting = Object::Instantiate(valueControllerTemplate, parent, false);
        auto gameObject = baseSetting->get_gameObject();
        Object::Destroy(baseSetting);
        gameObject->SetActive(false);

        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        static ConstString name{"BSMLIncDecSetting"};
        gameObject->set_name(name);
        
        // since we require the tag to be made with a type that inherits IncDecSetting, we can use that as the holder for the value;
        IncDecSetting* setting = reinterpret_cast<IncDecSetting*>(gameObject->AddComponent(get_type()));
        auto firstChild = transform->GetChild(1)->get_gameObject();

        setting->text = firstChild->GetComponentsInChildren<TMPro::TextMeshProUGUI*>().First();
        setting->text->set_richText(true);
        setting->text->set_overflowMode(TMPro::TextOverflowModes::Ellipsis);
        
        auto buttons = firstChild->GetComponentsInChildren<Button*>();
        setting->decButton = buttons.First();
        setting->incButton = buttons.Last();
        reinterpret_cast<RectTransform*>(firstChild->get_transform())->set_sizeDelta({40, 0});

        // text stuff
        auto nameText = transform->Find("NameText")->get_gameObject();
        Object::Destroy(nameText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());
        
        TMPro::TextMeshProUGUI* text = nameText->GetComponent<TMPro::TextMeshProUGUI*>();
        text->set_richText(true);
        text->set_text("BSMLIncDecSetting");
        
        // layout stuff
        auto layoutElement = gameObject->GetComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(90);

        gameObject->SetActive(true);

        // apply parsed information
        textMeshProUGUIData.Apply(text);
        rectTransformData.Apply(transform);
        layoutElementData.Apply(layoutElement);

        return gameObject;
    }

    void IncDecSettingTagBase::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing incdecsetting tag");
        this->::BSML::BSMLTag::parse(elem);

        genericSettingData = GenericSettingData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        layoutElementData = LayoutElementData(elem);
        rectTransformData = RectTransformData(elem);
    }
}