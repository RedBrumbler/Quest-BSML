#include "BSML/Tags/TextTag.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"

#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace BSML {
    void TextTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        SetHostField(host, go->GetComponent<TMPro::TextMeshProUGUI*>());
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* TextTag::CreateObject(UnityEngine::Transform* parent) const {
        auto text = CreateText(parent, textMeshProUGUIData.get_text(), textMeshProUGUIData.get_italics().value_or(true));
        textMeshProUGUIData.Apply(text);
        rectTransformData.Apply(text->get_rectTransform());

        return text->get_gameObject();
    }

    void TextTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing text tag");
        this->::BSML::BSMLTag::parse(elem);
        
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        rectTransformData = RectTransformData(elem);
    }
}