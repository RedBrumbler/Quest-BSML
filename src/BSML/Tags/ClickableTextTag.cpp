#include "BSML/Tags/ClickableTextTag.hpp"
#include "BSML/Components/ClickableText.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"
#include "logging.hpp"

#include "HMUI/Touchable.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

#include "GlobalNamespace/Signal.hpp"
#include "GlobalNamespace/MenuShockwave.hpp"
#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"

using namespace UnityEngine;
using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace BSML {
    static BSMLNodeParser<ClickableTextTag> clickableTextTagParser({"clickable-text"});

    GlobalNamespace::Signal get_textClickedSignal() {
        static SafePtrUnity<GlobalNamespace::Signal> textClickedSignal;
        if (!textClickedSignal) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave>().FirstOrDefault();
            textClickedSignal = menuShockWave ? menuShockWave.buttonClickEvents.LastOrDefault() : nullptr;
        }
        return GlobalNamespace::Signal(textClickedSignal.ptr());
    }

    HapticPresetSO get_textHapticPreset() {
        static SafePtrUnity<HapticPresetSO> textHapticPreset;
        if (!textHapticPreset) {
            textHapticPreset = UnityEngine::ScriptableObject::CreateInstance<HapticPresetSO>();
            textHapticPreset.duration = 0.02f;
            textHapticPreset.strength = 1.0f;
            textHapticPreset.frequency = 0.2f;
            Object::DontDestroyOnLoad(textHapticPreset.ptr());
        }
        return HapticPresetSO(textHapticPreset.ptr());
    }

    GlobalNamespace::HapticFeedbackController get_textHapticFeedbackController() {
        static SafePtrUnity<GlobalNamespace::HapticFeedbackController> textHapticFeedbackController;
        if (!textHapticFeedbackController) {
            textHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackController>();
        }
        return GlobalNamespace::HapticFeedbackController(textHapticFeedbackController.ptr());
    }

    UnityEngine::GameObject ClickableTextTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Clickable text");
        auto gameObject = GameObject::New_ctor("BSMLClickableText");
        gameObject.SetActive(false);
        gameObject.transform.SetParent(parent, false);

        auto textMesh = gameObject.AddComponent<ClickableText>();
        textMesh.font = Helpers::GetMainTextFont();
        textMesh.fontSharedMaterial = Helpers::GetMainUIFontMaterial();
        textMesh.text = "BSMLClickableText";
        textMesh.fontSize = 4;
        textMesh.color = {1.0f, 1.0f, 1.0f, 1.0f};
        textMesh.richText = true;

        auto rectTransform = textMesh.rectTransform;
        rectTransform.anchorMin = {0.5f, 0.5f};
        rectTransform.anchorMax = {0.5f, 0.5f};
        rectTransform.sizeDelta = {90, 8};

        gameObject.AddComponent<UI::LayoutElement>();

        textMesh.buttonClickedSignal = get_textClickedSignal();
        textMesh.hapticFeedbackPresetSO = get_textHapticPreset();
        textMesh.hapticFeedbackController = get_textHapticFeedbackController();

        gameObject.SetActive(true);
        return gameObject;
    }
}
