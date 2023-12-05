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
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "HMUI/AnimatedSwitchView.hpp"
#include "GlobalNamespace/FormattedFloatListSettingsValueController.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ColorSettingTag> colorSettingTagParser({"color-setting"});

    GlobalNamespace::FormattedFloatListSettingsValueController get_baseSettings() {
        static SafePtrUnity<GlobalNamespace::FormattedFloatListSettingsValueController> baseSettings;
        if (!baseSettings) {
            baseSettings = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController>().FirstOrDefault([](auto x){ return x.name == "VRRenderingScale"; });
        }
        return GlobalNamespace::FormattedFloatListSettingsValueController(baseSettings.ptr());
    }

    Image* get_colorImage() {
        static SafePtrUnity<Image> colorImage;
        if (!colorImage)
            colorImage = Resources::FindObjectsOfTypeAll<Image>().FirstOrDefault([](auto x) {
                if (x.name != "ColorImage") return false;
                auto sprite = x.sprite;
                if (!sprite) return false;
                return sprite.name == "NoteCircle";
            });
        return colorImage.ptr();
    }

    UnityEngine::GameObject ColorSettingTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating ColorSetting");

        auto baseSetting = Object::Instantiate(get_baseSettings(), parent, false);
        auto gameObject = baseSetting.gameObject;
        auto externalComponents = gameObject.AddComponent<BSML::ExternalComponents>();
        gameObject.SetActive(false);
        gameObject.name = "BSMLColorSetting";
        externalComponents.Add(gameObject.transform);

        Object::Destroy(baseSetting);
        auto colorSetting = gameObject.AddComponent<BSML::ColorSetting>();
        externalComponents.Add(colorSetting);

        auto valuePick = gameObject.transform.Find("ValuePicker").gameObject;
        RectTransform(valuePick.transform.convert()).sizeDelta = {13, 0};

        auto buttons = valuePick.GetComponentsInChildren<Button>();
        auto decButton = buttons.FirstOrDefault();
        decButton.enabled = false;
        decButton.interactable = true;
        Object::Destroy(decButton.transform.Find("Icon").gameObject);
        Object::Destroy(valuePick.GetComponentsInChildren<TMPro::TextMeshProUGUI>().FirstOrDefault().gameObject);
        colorSetting.editButton = buttons.LastOrDefault();

        auto nameText = gameObject.transform.Find("NameText").gameObject;
        Object::Destroy(nameText.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());

        auto text = nameText.GetComponent<TMPro::TextMeshProUGUI>();
        text.text = "BSMLColorSetting";
        externalComponents.Add(text);

        auto layoutElement = gameObject.GetComponent<LayoutElement>();
        layoutElement.preferredWidth = 90.0f;
        externalComponents.Add(layoutElement);

        colorSetting.colorImage = Object::Instantiate(get_colorImage(), valuePick.transform, false);
        colorSetting.colorImage.name = "BSMLCurrentColor";
        RectTransform colorImageTransform {colorSetting.colorImage.transform.convert()};
        colorImageTransform.anchoredPosition = {0, 0};
        colorImageTransform.sizeDelta = {5, 5};
        colorImageTransform.anchorMin = {0.2f, 0.5f};
        colorImageTransform.anchorMax = {0.2f, 0.5f};
        externalComponents.Add(colorSetting.colorImage);

        auto icon = colorSetting.editButton.transform.Find("Icon").GetComponent<Image>();
        icon.name = "EditIcon";
        icon.sprite = Utilities::FindSpriteCached("EditIcon");
        icon.rectTransform.sizeDelta = {4, 4};
        colorSetting.editButton.interactable = true;

        RectTransform(colorSetting.editButton.transform.convert()).anchorMin = {0, 0};

        colorSetting.modalColorPicker = Base::CreateObject(gameObject.transform).GetComponent<ModalColorPicker>();
        externalComponents.Add(colorSetting.modalColorPicker);

        gameObject.SetActive(true);
        return gameObject;
    }
}
