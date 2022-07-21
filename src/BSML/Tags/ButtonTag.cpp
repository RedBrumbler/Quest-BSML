#include "BSML/Tags/ButtonTag.hpp"
#include "logging.hpp"

#include "UnityEngine/UI/Button.hpp"
#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace BSML {
    void ButtonTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto button = go->GetComponent<UnityEngine::UI::Button*>();
        buttonData.Apply(button, host);

        SetHostField(host, button);
        
        CreateChildren(go->get_transform(), host);

    }

    UnityEngine::GameObject* ButtonTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Button");
        auto button = CreateUIButton(parent, "");
        auto gameObject = button->get_gameObject();
        selectableData.Apply(button);

        textMeshProUGUIData.Apply(gameObject->GetComponentInChildren<TMPro::TextMeshProUGUI*>());
        contentSizeFitterData.Apply(gameObject->GetComponent<UnityEngine::UI::ContentSizeFitter*>());
        layoutElementData.Apply(gameObject->GetComponent<UnityEngine::UI::LayoutElement*>());
        layoutGroupData.Apply(gameObject->GetComponent<UnityEngine::UI::LayoutGroup*>());
        rectTransformData.Apply(reinterpret_cast<UnityEngine::RectTransform*>(button->get_transform()));

        return gameObject;
    }

    void ButtonTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing horizontal tag");
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