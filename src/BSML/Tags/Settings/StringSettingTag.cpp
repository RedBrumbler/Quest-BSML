#include "BSML/Tags/Settings/StringSettingTag.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/StringSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/UI/Image.hpp"
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
    GlobalNamespace::FormattedFloatListSettingsValueController* valueControllerTemplate = nullptr;
    
    void StringSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto externalComponents = go->GetComponent<ExternalComponents*>();
        auto stringSetting = externalComponents->Get<BSML::StringSetting*>();

        auto modalView = externalComponents->Get<BSML::ModalView*>();
        modalView->dismissOnBlockerClicked = true;
        modalView->moveToCenter = true;

        auto keyboard = externalComponents->Get<BSML::ModalKeyboard*>();
        keyboard->genericSetting->Finalize();
        keyboard->genericSetting = nullptr;
        
        genericSettingData.Apply(stringSetting->genericSetting, host);
        rectTransformData.Apply(externalComponents->Get<RectTransform*>());
        textMeshProUGUIData.Apply(externalComponents->Get<TMPro::TextMeshProUGUI*>());
        layoutElementData.Apply(externalComponents->Get<LayoutElement*>());

        SetHostField(host, stringSetting);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* StringSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating StringSetting");
        if (!valueControllerTemplate || !Object::IsNativeObjectAlive(valueControllerTemplate)) {
            valueControllerTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::FormattedFloatListSettingsValueController*>().FirstOrDefault([](auto x){ return x->get_gameObject()->get_name() == "VRRenderingScale"; });
        }
        auto baseSetting = Object::Instantiate(valueControllerTemplate, parent, false);
        baseSetting->set_name("BSMLStringSetting");
        
        auto gameObject = baseSetting->get_gameObject();
        gameObject->SetActive(false);
        Object::Destroy(baseSetting);

        auto stringSetting = gameObject->AddComponent<BSML::StringSetting*>();
        auto valuePick = gameObject->get_transform()->Find("ValuePicker");
        Object::Destroy(valuePick->GetComponent<GlobalNamespace::StepValuePicker*>());

        auto buttons = valuePick->GetComponentsInChildren<Button*>();
        auto decButton = buttons.FirstOrDefault();
        decButton->set_enabled(false);
        decButton->set_interactable(true);
        Object::Destroy(decButton->get_transform()->Find("Icon")->get_gameObject());
        stringSetting->text = valuePick->GetComponentsInChildren<TMPro::TextMeshProUGUI*>().FirstOrDefault();
        stringSetting->text->set_richText(true);
        stringSetting->text->set_text("");
        stringSetting->editButton = buttons.LastOrDefault();
        stringSetting->boundingBox = reinterpret_cast<RectTransform*>(valuePick);

        auto nameText = gameObject->get_transform()->Find("NameText")->get_gameObject();
        Object::Destroy(nameText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());

        auto text = nameText->GetComponent<TMPro::TextMeshProUGUI*>();
        text->set_text("BSMLStringSetting");

        auto layoutElement = gameObject->GetComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(90.0f);
        stringSetting->text->set_alignment(TMPro::TextAlignmentOptions::MidlineRight);
        stringSetting->text->set_enableWordWrapping(false);
        auto textTransform = reinterpret_cast<RectTransform*>(stringSetting->text->get_transform());
        textTransform->set_anchorMin({0, 0});
        textTransform->set_anchorMax({1, 1});
        textTransform->set_anchoredPosition({-6, 0});

        auto icon = stringSetting->editButton->get_transform()->Find("Icon")->GetComponent<Image*>();
        icon->set_name("EditIcon");
        icon->set_sprite(Utilities::FindSpriteCached("EditIcon"));
        icon->get_rectTransform()->set_sizeDelta({4, 4});
        stringSetting->editButton->set_interactable(true);
        reinterpret_cast<RectTransform*>(stringSetting->editButton->get_transform())->set_anchorMin({0, 0});

        auto baseObject = Base::CreateObject(gameObject->get_transform());
        auto externalComponents = gameObject->AddComponent<ExternalComponents*>();
        stringSetting->modalKeyboard = baseObject->GetComponent<BSML::ModalKeyboard*>();
        externalComponents->Add(gameObject->get_transform());
        externalComponents->Add(baseObject->GetComponent<BSML::ModalView*>());
        externalComponents->Add(stringSetting->modalKeyboard);
        externalComponents->Add(stringSetting);
        externalComponents->Add(text);
        externalComponents->Add(layoutElement);

        gameObject->SetActive(true);
        return gameObject;
    }

    void StringSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing string setting tag");
        this->Base::parse(elem);

        genericSettingData = GenericSettingData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        layoutElementData = LayoutElementData(elem);
    }
}