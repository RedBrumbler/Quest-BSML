#include "BSML/Toast/Toast.hpp"
#include "BSML/Animations/AnimationStateUpdater.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    void SimpleImage::apply(HMUI::ImageView* img) {
        // remove state updater if it's there
        auto oldStateUpdater = img->GetComponent<AnimationStateUpdater*>();
        if (oldStateUpdater) {
            UnityEngine::Object::DestroyImmediate(oldStateUpdater);
        }
        img->set_sprite(image);
    }

    void BSMLImage::apply(HMUI::ImageView* img) {
        BSML::Utilities::SetImage(img, path);
    }
}
