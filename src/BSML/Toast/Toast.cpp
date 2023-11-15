#include "BSML/Toast/Toast.hpp"
#include "BSML/Animations/AnimationStateUpdater.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    Toast Toast::warning(std::string_view subtext, std::function<void()> onClick) {
        return Toast(
            "Warning",
            subtext,
            ImageSetup::FromPath(MOD_ID "_toast_warning"),
            5.0f,
            onClick,
            {1.0f, 0.3f, 0.0f, 1.0f}
        );
    }

    Toast Toast::error(std::string_view subtext, std::function<void()> onClick) {
        return Toast(
            "Error",
            std::string(subtext),
            ImageSetup::FromPath(MOD_ID "_toast_error"),
            5.0f,
            onClick,
            {1.0f, 0.1f, 0.1f, 1.0f}
        );
    }

    Toast Toast::info(std::string_view subtext, std::function<void()> onClick) {
        return Toast(
            "Info",
            std::string(subtext),
            ImageSetup::FromPath(MOD_ID "_toast_info"),
            5.0f,
            onClick,
            {0.5f, 0.8f, 0.9f, 1.0f}
        );
    }

    Toast Toast::debug(std::string_view subtext, std::function<void()> onClick) {
        return Toast(
            "Debug",
            std::string(subtext),
            ImageSetup::FromPath(MOD_ID "_toast_debug"),
            5.0f,
            onClick,
            {0.2f, 1.0f, 0.3f, 1.0f}
        );
    }

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
