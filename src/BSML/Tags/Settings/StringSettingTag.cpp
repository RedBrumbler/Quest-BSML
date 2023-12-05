#include "BSML/Tags/Settings/StringSettingTag.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/StringSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "GlobalNamespace/FormattedFloatListSettingsValueController.hpp"
#include "GlobalNamespace/StepValuePicker.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<StringSettingTag> stringSettingTagParser({"string-setting"});
    GlobalNamespace::FormattedFloatListSettingsValueController get_stringValueControllerTemplate() {
        static SafePtrUnity<GlobalNamespace::FormattedFloatListSettingsValueController> stringValueControllerTemplate;
        if (!stringValueControllerTemplate) {
            stringValueControllerTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController>().FirstOrDefault([](auto x){ return x.name == "VRRenderingScale"; });
        }
        return GlobalNamespace::FormattedFloatListSettingsValueController(stringValueControllerTemplate.ptr());
    }

    UnityEngine::GameObject StringSettingTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating StringSetting");
        auto baseSetting = Object::Instantiate(get_stringValueControllerTemplate(), parent, false);
        baseSetting.name = "BSMLStringSetting";

        auto gameObject = baseSetting.gameObject;
        gameObject.SetActive(false);
        Object::Destroy(baseSetting);

        auto stringSetting = gameObject.AddComponent<BSML::StringSetting>();
        auto valuePick = gameObject.transform.Find("ValuePicker");
        Object::Destroy(valuePick.GetComponent<GlobalNamespace::StepValuePicker>());

        auto buttons = valuePick.GetComponentsInChildren<Button>();
        auto decButton = buttons.FirstOrDefault();
        decButton.enabled = false;
        decButton.interactable = true;
        Object::Destroy(decButton.transform.Find("Icon").gameObject);
        stringSetting.text = valuePick.GetComponentsInChildren<TMPro::TextMeshProUGUI>().FirstOrDefault();
        stringSetting.text.richText = true;
        stringSetting.text.text = "";
        stringSetting.editButton = buttons.LastOrDefault();
        stringSetting.boundingBox = RectTransform(valuePick.convert());

        auto nameText = gameObject.transform.Find("NameText").gameObject;
        Object::Destroy(nameText.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());

        auto text = nameText.GetComponent<TMPro::TextMeshProUGUI>();
        text.text = "BSMLStringSetting";

        auto layoutElement = gameObject.GetComponent<LayoutElement>();
        layoutElement.preferredWidth = 90.0f;
        stringSetting.text.alignment = TMPro::TextAlignmentOptions::MidlineRight;
        stringSetting.text.enableWordWrapping = false;
        RectTransform textTransform {stringSetting.text.transform.convert()};
        textTransform.anchorMin = {0, 0};
        textTransform.anchorMax = {1, 1};
        textTransform.anchoredPosition = {-6, 0};

        auto icon = stringSetting.editButton.transform.Find("Icon").GetComponent<Image>();
        icon.name = "EditIcon";
        icon.sprite = Utilities::FindSpriteCached("EditIcon");
        icon.rectTransform.sizeDelta = {4, 4};
        stringSetting.editButton.interactable = true;
        RectTransform(stringSetting.editButton.transform.convert()).anchorMin = {0, 0};

        auto baseObject = Base::CreateObject(gameObject.transform);
        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        stringSetting.modalKeyboard = baseObject.GetComponent<BSML::ModalKeyboard>();
        externalComponents.Add(gameObject.transform);
        externalComponents.Add(baseObject.GetComponent<BSML::ModalView>());
        externalComponents.Add(stringSetting.modalKeyboard);
        externalComponents.Add(stringSetting);
        externalComponents.Add(text);
        externalComponents.Add(layoutElement);

        gameObject.SetActive(true);
        return gameObject;
    }
}
