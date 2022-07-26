#pragma once

#include "UnityEngine/Sprite.hpp"

namespace BSML::Utilities {
    /// @brief Finds a sprite by name.
    UnityEngine::Sprite* FindSpriteCached(StringW name);
}