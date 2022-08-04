#include "BSML/Tags/ClickableImageTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/ClickableImage.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/ImageView.hpp"

#include "GlobalNamespace/Signal.hpp"
#include "GlobalNamespace/MenuShockwave.hpp"
#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"

using namespace UnityEngine;
using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace BSML {
    static BSMLNodeParser<ClickableImageTag> imageTagParser({"clickable-image", "clickable-img"});
    
    GlobalNamespace::Signal* imageClickedSignal = nullptr;
    HapticPresetSO* imageHapticPreset = nullptr;
    GlobalNamespace::HapticFeedbackController* imageHapticFeedbackController = nullptr;

    UnityEngine::GameObject* ClickableImageTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Image");
        auto gameObject = GameObject::New_ctor("BSMLClickableImage");
        auto image = gameObject->AddComponent<ClickableImage*>();
        image->set_material(Helpers::GetUINoGlowMat());
        auto rectTransform = image->get_rectTransform();
        rectTransform->set_sizeDelta({20, 20});
        rectTransform->SetParent(parent, false);
        // TODO: maybe use a default placeholder sprite instead? maybe a BSML image
        image->set_sprite(Utilities::ImageResources::GetBlankSprite());

        if (!imageClickedSignal || !Object::IsNativeObjectAlive(imageClickedSignal)) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave*>().FirstOrDefault();
            imageClickedSignal = menuShockWave ? menuShockWave->buttonClickEvents.LastOrDefault() : nullptr;
        }

        if (!imageHapticPreset || !Object::IsNativeObjectAlive(imageHapticPreset)) {
            imageHapticPreset = UnityEngine::ScriptableObject::CreateInstance<HapticPresetSO*>();
            imageHapticPreset->duration = 0.02f;
            imageHapticPreset->strength = 1.0f;
            imageHapticPreset->frequency = 0.2f;
            Object::DontDestroyOnLoad(imageHapticPreset);
        }
        
        if (!imageHapticFeedbackController || !Object::IsNativeObjectAlive(imageHapticFeedbackController)) {
            imageHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackController*>();
        }

        image->buttonClickedSignal = imageClickedSignal;
        image->hapticFeedbackController = imageHapticFeedbackController;
        image->hapticFeedbackPresetSO = imageHapticPreset;

        gameObject->AddComponent<UI::LayoutElement*>();
        return gameObject;
    }
}