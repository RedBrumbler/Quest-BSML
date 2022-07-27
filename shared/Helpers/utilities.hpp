#pragma once

#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "System/Uri.hpp"

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

    struct ScaleOptions {
        int width;
        int height;
        bool maintainRatio;
        bool shouldScale;

        ScaleOptions(int width = 0, int height = 0, bool maintainRatio = true, bool shouldScale = false)
            : width(width)
            , height(height)
            , maintainRatio(maintainRatio)
            , shouldScale(shouldScale)
        {}
    };

    /// @brief sets the sprite from a path, this does not yet bother with animated textures so it will only work with base textures
    /// @param image the image to set the sprite on
    /// @param path the path, basegame name, or URI to an image
    void SetImage(UnityEngine::UI::Image* image, StringW path);

    /// @brief sets the sprite from a path, this does not yet bother with animated textures so it will only work with base textures
    /// @param image the image to set the sprite on
    /// @param path the path, basegame name, or URI to an image
    /// @param loadingAnimation currently unused, but might eventually be used for a loading animation while stuff is downloading
    /// @param scaleOptions the scale options to use, if any
    /// @param onFinished a callback to call when the image is finished loading, if any
    void SetImage(UnityEngine::UI::Image* image, StringW path, bool loadingAnimation, ScaleOptions scaleOptions, std::function<void()> onFinished = nullptr);

    /// @brief function to get data at a URI, this is not blocking as it dispatches a coroutine
    /// @param uri the URI to get data from
    /// @param onFinished what to do with the downloaded bytes
    void GetData(System::Uri* uri, std::function<void(ArrayW<uint8_t>)> onFinished = nullptr);

    /// @brief function to get data from the key to data cache, this is blocking due to the data being available immediately
    /// @param key the key to get the data with
    /// @param onFinished what to do with the downloaded bytes
    void GetData(StringW key, std::function<void(ArrayW<uint8_t>)> onFinished = nullptr);

    /// @brief Function to load a sprite from a data array
    /// @param data the data to load the sprite from
    /// @param pixelsPerUnit the pixels per unit
    /// @return created sprite
    UnityEngine::Sprite* LoadSpriteRaw(ArrayW<uint8_t> data, float pixelsPerUnit = 100.0f);

    /// @brief Function to load a sprite from a texture
    /// @param texture the texture to use
    /// @param pixelsPerUnit the pixels per unit
    /// @return created sprite
    UnityEngine::Sprite* LoadSpriteFromTexture(UnityEngine::Texture2D* texture, float pixelsPerUnit = 100.0f);

    /// @brief Function to load a texture from a data array
    /// @param data the data to load the texture from
    /// @return created texture
    UnityEngine::Texture2D* LoadTextureRaw(ArrayW<uint8_t> data);
}