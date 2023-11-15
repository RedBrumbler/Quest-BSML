#pragma once

#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include <string>

namespace BSML {
    struct Toast {
        /// @brief title of the toast, big text at the top
        std::string title = "";
        /// @brief subtext, smaller text
        std::string subtext = "";
        /// @brief image displayed to the left
        UnityEngine::Sprite* image = nullptr;
        /// @brief how long is this toast to be displayed
        float displayTime = 5.0f;
        /// @brief called when the toast is clicked
        std::function<void()> onClick = nullptr;
        /// @brief accent color for the left of the toast
        UnityEngine::Color accentColor = {1, 1, 1, 1};
    };
}
