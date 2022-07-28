#include "BSML/Tags/ButtonTag.hpp"

#include "BSML/Components/ExternalComponents.hpp"
#include "logging.hpp"

#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/LayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ButtonTag> buttonTagParser({"button"});
    Button* buttonPrefab = nullptr;
    Button* ButtonTag::get_buttonPrefab() const {
        if (!buttonPrefab || !Object::IsNativeObjectAlive(buttonPrefab)) {
            buttonPrefab = Resources::FindObjectsOfTypeAll<Button*>().LastOrDefault([&](auto x){ return x->get_name() == "PracticeButton"; });
        }
        return buttonPrefab;
    }

    void ButtonTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto externalComponents = go->GetComponent<ExternalComponents*>();
        auto button = externalComponents->Get<Button*>();

        buttonData.Apply(button, host);
        selectableData.Apply(button);
        textMeshProUGUIData.Apply(externalComponents->Get<TMPro::TextMeshProUGUI*>());
        contentSizeFitterData.Apply(externalComponents->Get<ContentSizeFitter*>());
        layoutElementData.Apply(externalComponents->Get<LayoutElement*>());
        layoutGroupData.Apply(externalComponents->Get<LayoutGroup*>());
        rectTransformData.Apply(externalComponents->Get<RectTransform*>());
        SetHostField(host, button);
        
        CreateChildren(go->get_transform(), host);

    }

    UnityEngine::GameObject* ButtonTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Button");

        auto button = Object::Instantiate(get_buttonPrefab(), parent, false);
        button->set_name("BSMLButton");
        button->set_interactable(true);

        auto transform = reinterpret_cast<RectTransform*>(button->get_transform());
        auto gameObject = button->get_gameObject();
        gameObject->SetActive(true);
        auto externalComponents = gameObject->AddComponent<ExternalComponents*>();
        externalComponents->Add(button);
        externalComponents->Add(transform);

        auto textObject = button->get_transform()->Find("Content/Text")->get_gameObject();
        Object::Destroy(textObject->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());
        
        auto textMesh = textObject->GetComponent<TMPro::TextMeshProUGUI*>();
        textMesh->set_text("BSMLButton");
        textMesh->set_richText(true);
        externalComponents->Add(textMesh);

        Object::Destroy(transform->Find("Content")->GetComponent<LayoutElement*>());
        
        auto buttonSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        buttonSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        buttonSizeFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
        externalComponents->Add(buttonSizeFitter);
        
        auto stackLayoutGroup = button->GetComponentInChildren<LayoutGroup*>();
        if (stackLayoutGroup)
            externalComponents->Add(stackLayoutGroup);

        auto layoutElement = gameObject->AddComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(30.0f);
        externalComponents->Add(layoutElement);

        return gameObject;
    }

    void ButtonTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing button tag");
        this->::BSML::BSMLTag::parse(elem);

        buttonData = ButtonData(elem);
        selectableData = SelectableData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        contentSizeFitterData = ContentSizeFitterData(elem);
        layoutElementData = LayoutElementData(elem);
        layoutGroupData = LayoutGroupData(elem);
        rectTransformData = RectTransformData(elem);
    }
}