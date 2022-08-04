#include "BSML/Tags/ClickableTextTag.hpp"
#include "BSML/Components/ClickableText.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

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

    GlobalNamespace::Signal* textClickedSignal = nullptr;
    HapticPresetSO* textHapticPreset = nullptr;
    GlobalNamespace::HapticFeedbackController* textHapticFeedbackController = nullptr;

    UnityEngine::GameObject* ClickableTextTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Clickable text");
        auto gameObject = GameObject::New_ctor("BSMLClickableText");
        gameObject->SetActive(false);
        gameObject->get_transform()->SetParent(parent, false);

        auto textMesh = gameObject->AddComponent<ClickableText*>();
        textMesh->set_font(Helpers::GetMainTextFont());
        textMesh->set_fontSharedMaterial(Helpers::GetMainUIFontMaterial());
        textMesh->set_text("BSMLClickableText");
        textMesh->set_fontSize(4);
        textMesh->set_color({1.0f, 1.0f, 1.0f, 1.0f});
        textMesh->set_richText(true);

        auto rectTransform = textMesh->get_rectTransform();
        rectTransform->set_anchorMin({0.5f, 0.5f});
        rectTransform->set_anchorMax({0.5f, 0.5f});
        rectTransform->set_sizeDelta({90, 8});
        
        gameObject->AddComponent<UI::LayoutElement*>();

        if (!textClickedSignal || !Object::IsNativeObjectAlive(textClickedSignal)) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave*>().FirstOrDefault();
            textClickedSignal = menuShockWave ? menuShockWave->buttonClickEvents.LastOrDefault() : nullptr;
        }

        if (!textHapticPreset || !Object::IsNativeObjectAlive(textHapticPreset)) {
            textHapticPreset = UnityEngine::ScriptableObject::CreateInstance<HapticPresetSO*>();
            textHapticPreset->duration = 0.02f;
            textHapticPreset->strength = 1.0f;
            textHapticPreset->frequency = 0.2f;
            Object::DontDestroyOnLoad(textHapticPreset);
        }
        if (!textHapticFeedbackController || !Object::IsNativeObjectAlive(textHapticFeedbackController)) {
            textHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackController*>();
        }

        textMesh->buttonClickedSignal = textClickedSignal;
        textMesh->hapticFeedbackController = textHapticFeedbackController;
        textMesh->hapticFeedbackPresetSO = textHapticPreset;

        gameObject->SetActive(true);
        return gameObject;
    }
}