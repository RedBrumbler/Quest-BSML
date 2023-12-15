#include "BSML/Tags/Settings/ColorSettingTag.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/Settings/ColorSetting.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/Vector2.hpp"
#include "HMUI/AnimatedSwitchView.hpp"
#include "GlobalNamespace/FormattedFloatListSettingsValueController.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ColorSettingTag> colorSettingTagParser({"color-setting"});

    GlobalNamespace::FormattedFloatListSettingsValueController* get_baseSettings() {
        static SafePtrUnity<GlobalNamespace::FormattedFloatListSettingsValueController> baseSettings;
        if (!baseSettings) {
            baseSettings = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController*>().FirstOrDefault([](auto x){ return x->get_name() == "VRRenderingScale"; });
        }
        return baseSettings.ptr();
    }

    Image* get_colorImage() {
        static SafePtrUnity<Image> colorImage;
        if (!colorImage)
            colorImage = Resources::FindObjectsOfTypeAll<Image*>().FirstOrDefault([](auto x) {
                if (x->get_name() != "ColorImage") return false;
                auto sprite = x->get_sprite();
                if (!sprite) return false;
                return sprite->get_name() == "NoteCircle";
            });
        return colorImage.ptr();
    }

    UnityEngine::GameObject* ColorSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating ColorSetting");

        auto baseSetting = Object::Instantiate(get_baseSettings(), parent, false);
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

        colorSetting->colorImage = Object::Instantiate(get_colorImage(), valuePick->get_transform(), false);
        colorSetting->colorImage->set_name("BSMLCurrentColor");
        auto colorImageTransform = reinterpret_cast<RectTransform*>(colorSetting->colorImage->get_transform());
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
}
