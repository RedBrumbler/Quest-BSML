#pragma once

#include "UnityEngine/Sprite.hpp"
#include <string>

namespace BSML {
    struct Toast {
        /// @brief title of the toast, big text at the top
        std::string title;
        /// @brief subtext, smaller text
        std::string subtext;
        /// @brief image displayed to the left
        UnityEngine::Sprite* image;
        /// @brief how long is this toast to be displayed
        float displayTime;
        /// @brief called when the toast is clicked
        std::function<void()> onClick;
    };
}
