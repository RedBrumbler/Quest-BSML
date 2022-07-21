#include "BSML/Tags/Settings/ToggleSettingTag.hpp"
#include "logging.hpp"

#include "UnityEngine/UI/Button.hpp"
#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace BSML {
    void ToggleSettingTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto toggle = go->GetComponentInChildren<UnityEngine::UI::Toggle*>();
        SetHostField(host, toggle);
        toggleSettingData.Apply(toggle, host);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* ToggleSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating ToggleSetting");
        auto toggle = CreateToggle(parent, "");
        auto gameObject = toggle->get_transform()->get_parent()->get_gameObject();
        auto nameText = gameObject->get_transform()->Find("NameText")->get_gameObject();

        // TODO: make it use the correct tmpro, instead of the first one it finds
        textMeshProUGUIData.Apply(nameText->GetComponent<TMPro::TextMeshProUGUI*>());
        layoutElementData.Apply(gameObject->GetComponent<UnityEngine::UI::LayoutElement*>());
        rectTransformData.Apply(reinterpret_cast<UnityEngine::RectTransform*>(gameObject->get_transform()));

        return gameObject;
    }

    void ToggleSettingTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing horizontal tag");
        this->::BSML::BSMLTag::parse(elem);

        toggleSettingData = ToggleSettingData(elem);
        textMeshProUGUIData = TextMeshProUGUIData(elem);
        layoutElementData = LayoutElementData(elem);
        rectTransformData = RectTransformData(elem);
    }
}