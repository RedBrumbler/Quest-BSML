#pragma once

#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include "HMUI/ImageView.hpp"
#include <string>

namespace BSML {
    struct Toast {
        /// @brief title of the toast, big text at the top
        std::string title = "";
        /// @brief subtext, smaller text
        std::string subtext = "";
        /// @brief image displayed to the left
        ImageSetup* imageSetup = nullptr;
        /// @brief how long is this toast to be displayed
        float displayTime = 5.0f;
        /// @brief called when the toast is clicked
        std::function<void()> onClick = nullptr;
        /// @brief accent color for the left of the toast
        UnityEngine::Color accentColor = {1, 1, 1, 1};
    };

    /// @brief struct that has a virtual method to apply an image to the toast
    struct ImageSetup {
        virtual void apply(HMUI::ImageView* img) = 0;
        ~ImageSetup() = default;
    };

    /// @brief Just sets the sprite
    struct SimpleImage : public ImageSetup {
        UnityEngine::Sprite* image;
        void apply(HMUI::ImageView* img) override;
    };

    /// @brief Uses BSML::Utilities::SetImage to apply an image, can be a gif
    struct BSMLImage : public ImageSetup {
        std::string path;
        void apply(HMUI::ImageView* img) override;
    };
}
