#include "BSML/Tags/Settings/SubmenuTag.hpp"
#include "BSML.hpp"
#include "BSML/Settings/UI/ModSettingsFlowCoordinator.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"
#include "BSML/Components/ClickableText.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Settings/SettingsMenu.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Resources.hpp"

using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace BSML {

    static BSMLNodeParser<SubmenuTag> submenuTagParser({"settings-submenu"});

    extern GlobalNamespace::Signal get_textClickedSignal();
    extern HapticPresetSO get_textHapticPreset();
    extern GlobalNamespace::HapticFeedbackController get_textHapticFeedbackController();

    ModSettingsFlowCoordinator get_flow() {
        static SafePtrUnity<ModSettingsFlowCoordinator> flow;
        if (!flow) {
            flow = UnityEngine::Resources::FindObjectsOfTypeAll<ModSettingsFlowCoordinator>().FirstOrDefault();
        }
        return ModSettingsFlowCoordinator(flow.ptr());
    }

    UnityEngine::GameObject SubmenuTag::CreateObject(UnityEngine::Transform parent) const {
        auto go = UnityEngine::GameObject::New_ctor("BSMLSubMenu");
        go.SetActive(false);

        auto clickableText = go.AddComponent<ClickableText>();
        clickableText.font = Helpers::GetMainTextFont();
        clickableText.fontSharedMaterial = Helpers::GetMainUIFontMaterial();
        clickableText.rectTransform.SetParent(parent, false);
        clickableText.text = "BSMLText";
        clickableText.fontSize = 4;
        clickableText.fontStyle = TMPro::FontStyles::Italic;
        clickableText.color = {1, 1, 1, 1};
        clickableText.rectTransform.sizeDelta = {90, 8};

        auto submenuController = Helpers::CreateViewController<HMUI::ViewController>();
        SettingsMenu::SetupViewControllerTransform(submenuController);

        clickableText.onClick += [submenuController](){
            auto flow = get_flow();
            if (flow) {
                flow.OpenMenu(submenuController, true, false);
            }
        };

        auto externalComponents = submenuController.gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(clickableText);
        externalComponents.Add(clickableText.rectTransform);

        return submenuController.gameObject;
    }
}
