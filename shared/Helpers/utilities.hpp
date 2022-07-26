#pragma once

#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"

namespace BSML::Utilities {
    /// @brief Finds a sprite by name.
    UnityEngine::Sprite* FindSpriteCached(StringW name);

    /// @brief parses a HTML color from given string view
    /// @param str the string view
    /// @return the color, or nullopt
    std::optional<UnityEngine::Color> ParseHTMLColorOpt(std::string_view str);

    /// @brief parses a HTML color from given string view
    /// @param str the string view
    /// @return the color, or white if invalid
    UnityEngine::Color ParseHMTMLColor(std::string_view str);

    /// @brief parses a HTML color from given string view
    /// @param str the string view
    /// @return the color32, or nullopt
    std::optional<UnityEngine::Color32> ParseHTMLColor32Opt(std::string_view str);

    /// @brief parses a HTML color from given string view
    /// @param str the string view
    /// @return the color32, or white if invalid
    UnityEngine::Color32 ParseHTMLColor32(std::string_view str);
}