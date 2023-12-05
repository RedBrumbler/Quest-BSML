#include "BSML/Components/Backgroundable.hpp"
#include "logging.hpp"
#include <map>

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/HideFlags.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"

DEFINE_TYPE(BSML, Backgroundable);

std::map<std::string, std::string> backgrounds = {
    { "round-rect-panel", "RoundRect10" },
    { "panel-top", "RoundRect10" },
    { "panel-fade-gradient", "RoundRect10Thin" },
    { "panel-top-gradient", "RoundRect10" },
    { "title-gradient", "RoundRect10" }
};

std::map<std::string, std::string> objectNames = {
    { "round-rect-panel", "KeyboardWrapper" },
    { "panel-top", "BG" },
    { "panel-fade-gradient", "Background" },
    { "panel-top-gradient", "BG" },
    { "title-gradient", "BG" }
};

std::map<std::string, std::string> objectParentNames = {
    { "round-rect-panel", "Wrapper" },
    { "panel-top", "PracticeButton" },
    { "panel-fade-gradient", "LevelListTableCell" },
    { "panel-top-gradient", "ActionButton" },
    { "title-gradient", "TitleViewController" }
};

template<typename T, typename U>
using Dictionary = System::Collections::Generic::Dictionary_2<T, U>;

SafePtr<Dictionary<StringW, HMUI::ImageView*>> backgroundCache;

using namespace UnityEngine;

namespace BSML {
    void Backgroundable::ApplyBackground(StringW name) {
        if (background) {
            ERROR("Can't apply backgrounds twice!");
            return;
        }

        auto backgroundNameItr = backgrounds.find(name);
        if (backgroundNameItr == backgrounds.end()) {
            ERROR("Unknown background name: {}, Skipping!", name);
            return;
        }

        if (!backgroundCache)
            backgroundCache.emplace(Dictionary<StringW, HMUI::ImageView>::New_ctor());

        HMUI::ImageView bgTemplate{nullptr};
        if (!backgroundCache.TryGetValue(name, byref(bgTemplate)) || (!bgTemplate || !bgTemplate.m_CachedPtr)) {
            if (!bgTemplate || !bgTemplate.m_CachedPtr) {
                backgroundCache.Remove(name);
            }

            bgTemplate = FindTemplate(name, backgroundNameItr->second);
            backgroundCache.Add(name, bgTemplate);
        }

        background = gameObject.AddComponent<HMUI::ImageView>();

        //Copy Image: some methods are probably not needed
		background.alphaHitTestMinimumThreshold = bgTemplate.alphaHitTestMinimumThreshold;
		background.color = bgTemplate.color;
		background.color0 = bgTemplate.color0;
		background.color1 = bgTemplate.color1;
		background.gradient = bgTemplate.gradient;
		background._gradientDirection = bgTemplate._gradientDirection;
        background._flipGradientColors = bgTemplate._flipGradientColors;
        background._skew = bgTemplate._skew;
		background.eventAlphaThreshold = bgTemplate.eventAlphaThreshold;
		background.fillAmount = bgTemplate.fillAmount;
		background.fillCenter = bgTemplate.fillCenter;
		background.fillClockwise = bgTemplate.fillClockwise;
		background.fillMethod = bgTemplate.fillMethod;
		background.fillOrigin = bgTemplate.fillOrigin;
		background.hideFlags = bgTemplate.hideFlags;
		background.maskable = bgTemplate.maskable;
		background.material = bgTemplate.material;
		background.onCullStateChanged = bgTemplate.onCullStateChanged;
		background.overrideSprite = bgTemplate.overrideSprite;
		background.pixelsPerUnitMultiplier = bgTemplate.pixelsPerUnitMultiplier;
		background.preserveAspect = bgTemplate.preserveAspect;
		background.raycastTarget = bgTemplate.raycastTarget;
		background.sprite = bgTemplate.sprite;
		background.tag = bgTemplate.tag;
		background.type = bgTemplate.type;
		background.useGUILayout = bgTemplate.useGUILayout;
		background.useLegacyMeshGeneration = bgTemplate.useLegacyMeshGeneration;
		background.useSpriteMesh = bgTemplate.useSpriteMesh;

        background.enabled = true;
    }

    void Backgroundable::ApplyColor(UnityEngine::Color color) {
        if (!background) {
            ERROR("No background exists yet!");
            return;
        }
        UnityEngine::Color color0{1.0, 1.0, 1.0, background.color0.a};
        UnityEngine::Color color1{1.0, 1.0, 1.0, background.color1.a};
        color.a = background.color.a;

        background.gradient = false;
        background.color0 = color0;
        background.color1 = color1;
        background.color = color;
    }

    void Backgroundable::ApplyGradient(UnityEngine::Color color0, UnityEngine::Color color1) {
        if (!background) {
            ERROR("No background exists yet!");
            return;
        }
        UnityEngine::Color color = {1.0, 1.0, 1.0, background.color.a};
        background.gradient = true;
        background.color = color;
        background.color0 = color0;
        background.color1 = color1;
    }

    void Backgroundable::ApplyColor0(UnityEngine::Color color) {
        if (!background) {
            ERROR("No background exists yet!");
            return;
        }

        ApplyGradient(color, background.color1);
    }

    void Backgroundable::ApplyColor1(UnityEngine::Color color) {
        if (!background) {
            ERROR("No background exists yet!");
            return;
        }

        ApplyGradient(background.color0, color);
    }


    void Backgroundable::ApplyAlpha(float alpha) {
        if (!background) {
            ERROR("No background exists yet!");
            return;
        }
        auto col = background.color;
        col.a = alpha;
        background.color = col;
    }

    HMUI::ImageView Backgroundable::FindTemplate(StringW name, StringW backgroundName) {
        auto objectName = objectNames.find(name)->second;
        auto parentName = objectParentNames.find(name)->second;

        auto images = Resources::FindObjectsOfTypeAll<HMUI::ImageView>();

        for (auto image : images) {
            auto sprite = image.sprite;
            if (!sprite || sprite.name != backgroundName) continue;

            auto parent = image.transform.parent;
            if (!parent || parent.name != parentName) continue;

            auto goName = image.gameObject.name;
            if (goName != objectName) continue;

            return image;
        }

        return HMUI::ImageView{nullptr};
    }
}
