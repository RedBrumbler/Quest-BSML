#include "BSML/Tags/Settings/ColorSettingTag.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/Settings/ColorSetting.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "HMUI/AnimatedSwitchView.hpp"
#include "GlobalNamespace/FormattedFloatListSettingsValueController.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ColorSettingTag> colorSettingTagParser({"color-setting"});
    GlobalNamespace::FormattedFloatListSettingsValueController* baseSettings = nullptr;
    Image* colorImage = nullptr;

    void ColorSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto externalComponents = go->GetComponent<BSML::ExternalComponents*>();
        auto colorSetting = externalComponents->Get<BSML::ColorSetting*>();
        SetHostField(host, colorSetting);
        
        genericSettingData.Apply(colorSetting->genericSetting, host);
        textMeshProUGUIData.Apply(externalComponents->Get<TMPro::TextMeshProUGUI*>());
        layoutElementData.Apply(externalComponents->Get<LayoutElement*>());
        rectTransformData.Apply(externalComponents->Get<RectTransform*>());

        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* ColorSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating ColorSetting");
        if (!baseSettings || !Object::IsNativeObjectAlive(baseSettings)) {
            baseSettings = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController*>().FirstOrDefault([](auto x){ return x->get_name() == "VRRenderingScale"; });
        }

        auto baseSetting = Object::Instantiate(baseSettings, parent, false);
        auto gameObject = baseSetting->get_gameObject();
        auto externalComponents = gameObject->AddComponent<BSML::ExternalComponents*>();
        gameObject->SetActive(false);
        gameObject->set_name("BSMLColorSetting");
        externalComponents->Add(gameObject->get_transform());

        Object::Destroy(baseSetting);
        auto colorSetting = gameObject->AddComponent<BSML::ColorSetting*>();
        externalComponents->Add(colorSetting);

        auto valuePick = gameObject->get_transform()->Find("ValuePicker")->get_gameObject();
        reinterpret_cast<RectTransform*>(valuePick->get_transform())->set_sizeDelta({13, 0});

        auto buttons = valuePick->GetComponentsInChildren<Button*>();
        auto decButton = buttons.FirstOrDefault();
        decButton->set_enabled(false);
        decButton->set_interactable(true);
        Object::Destroy(decButton->get_transform()->Find("Icon")->get_gameObject());
        Object::Destroy(valuePick->GetComponentsInChildren<TMPro::TextMeshProUGUI*>().FirstOrDefault()->get_gameObject());
        colorSetting->editButton = buttons.LastOrDefault();

        auto nameText = gameObject->get_transform()->Find("NameText")->get_gameObject();
        Object::Destroy(nameText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());

        auto text = nameText->GetComponent<TMPro::TextMeshProUGUI*>();
        text->set_text("BSMLColorSetting");
        externalComponents->Add(text);
        
        auto layoutElement = gameObject->GetComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(90.0f);
        externalComponents->Add(layoutElement);

        if (!colorImage || !Object::IsNativeObjectAlive(colorImage))
            colorImage = Resources::FindObjectsOfTypeAll<Image*>().FirstOrDefault([](auto x) {
                if (x->get_name() != "ColorImage") return false;
                auto sprite = x->get_sprite();
                if (!sprite) return false;
                return sprite->get_name() == "NoteCircle";
            });
        colorSetting->colorImage = Object::Instantiate(colorImage, valuePick->get_transform(), false);
        colorSetting->colorImage->set_name("BSMLCurrentColor");
        auto colorImageTransform = reinterpret_cast<RectTransform*>(colorImage->get_transform());
        colorImageTransform->set_anchoredPosition({0, 0});
        colorImageTransform->set_sizeDelta({5, 5});
        colorImageTransform->set_anchorMin({0.2f, 0.5f});
        colorImageTransform->set_anchorMax({0.2f, 0.5f});
        externalComponents->Add(colorSetting->colorImage);

        auto icon = colorSetting->editButton->get_transform()->Find("Icon")->GetComponent<Image*>();
        icon->set_name("EditIcon");
        icon->set_sprite(Utilities::FindSpriteCached("EditIcon"));
        icon->get_rectTransform()->set_sizeDelta({4, 4});
        colorSetting->editButton->set_interactable(true);

        reinterpret_cast<RectTransform*>(colorSetting->editButton->get_transform())->set_anchorMin({0, 0});

        colorSetting->modalColorPicker = Base::CreateObject(gameObject->get_transform())->GetComponent<ModalColorPicker*>();
        externalComponents->Add(colorSetting->modalColorPicker);

        gameObject->SetActive(true);
        return gameObject;
    }

    void ColorSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing color setting tag");
        this->Base::parse(elem);

        genericSettingData = GenericSettingData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        layoutElementData = LayoutElementData(elem);
    }
}