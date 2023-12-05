#include "BSML/Tags/ModifierTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/ToggleSetting.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "GlobalNamespace/GameplayModifierToggle.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "HMUI/HoverTextSetter.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ModifierTag> modifierTagParser({"modifier", "modifier-toggle"});

    GlobalNamespace::GameplayModifierToggle get_gameplayModifierToggleTemplate() {
        static SafePtrUnity<GlobalNamespace::GameplayModifierToggle> gameplayModifierToggleTemplate;
        if (!gameplayModifierToggleTemplate)
            gameplayModifierToggleTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayModifierToggle>().FirstOrDefault();
        return GlobalNamespace::GameplayModifierToggle(gameplayModifierToggleTemplate.ptr());
    }

    UnityEngine::GameObject ModifierTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Modifier");

        auto gameplayModifierToggleTemplate = get_gameplayModifierToggleTemplate();
        auto baseModifier = Object::Instantiate(gameplayModifierToggleTemplate, parent, false);
        baseModifier.name = "BSMLModifier";

        auto gameObject = baseModifier.gameObject;
        gameObject.SetActive(false);
        RectTransform transform {gameObject.transform};
        Object::Destroy(baseModifier);
        Object::Destroy(gameObject.GetComponent<HMUI::HoverTextSetter>());
        Object::Destroy(transform.Find("Multiplier").gameObject);

        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        auto text = transform.Find("Name").GetComponent<TMPro::TextMeshProUGUI>();
        text.text = "BSMLModifier";
        externalComponents.Add(text);
        externalComponents.Add(transform.Find("Icon").GetComponent<Image>());

        auto toggleSetting = gameObject.AddComponent<ToggleSetting>();
        toggleSetting.toggle = gameObject.GetComponent<Toggle>();
        toggleSetting.text = text;

        gameObject.SetActive(true);
        return gameObject;
    }

}
