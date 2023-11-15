#pragma once

#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include "HMUI/ImageView.hpp"
#include <string>

namespace BSML {
    /// @brief struct that has a virtual method to apply an image to the toast
    struct ImageSetup {
        ImageSetup() {}
        virtual void apply(HMUI::ImageView* img) = 0;
        ~ImageSetup() = default;

        static inline std::shared_ptr<ImageSetup> FromImage(UnityEngine::Sprite* image);
        static inline std::shared_ptr<ImageSetup> FromPath(std::string_view path);
    };

    /// @brief Just sets the sprite
    struct SimpleImage : public ImageSetup {
        SimpleImage(UnityEngine::Sprite* image) : ImageSetup(), image(image) {}
        UnityEngine::Sprite* image;
        void apply(HMUI::ImageView* img) override;
    };

    /// @brief Uses BSML::Utilities::SetImage to apply an image, can be a gif
    struct BSMLImage : public ImageSetup {
        BSMLImage(std::string_view path) : ImageSetup(), path(path) {}
        std::string path;
        void apply(HMUI::ImageView* img) override;
    };

    inline std::shared_ptr<ImageSetup> ImageSetup::FromImage(UnityEngine::Sprite* image) { return std::make_shared<SimpleImage>(image); }
    inline std::shared_ptr<ImageSetup> ImageSetup::FromPath(std::string_view path) { return std::make_shared<BSMLImage>(path); }

    struct Toast {
        Toast() {};
        Toast(std::string_view title, std::string_view subtext, std::shared_ptr<ImageSetup> imageSetup, float displayTime, std::function<void()> onClick, UnityEngine::Color accentColor) : title(title), subtext(subtext), imageSetup(imageSetup), displayTime(displayTime), onClick(onClick), accentColor(accentColor) {}
        /// @brief title of the toast, big text at the top
        std::string title = "";
        /// @brief subtext, smaller text
        std::string subtext = "";
        /// @brief image displayed to the left
        std::shared_ptr<ImageSetup> imageSetup = ImageSetup::FromPath("#InfoIcon");
        /// @brief how long is this toast to be displayed
        float displayTime = 5.0f;
        /// @brief called when the toast is clicked
        std::function<void()> onClick = nullptr;
        /// @brief accent color for the left of the toast
        UnityEngine::Color accentColor = {1, 1, 1, 1};

        static Toast warning(std::string_view subtext, std::function<void()> onClick = nullptr);
        static Toast error(std::string_view subtext, std::function<void()> onClick = nullptr);
        static Toast info(std::string_view subtext, std::function<void()> onClick = nullptr);
        static Toast debug(std::string_view subtext, std::function<void()> onClick = nullptr);
        private:
            friend class ToastViewController;
            int handle = 0;
    };
}
