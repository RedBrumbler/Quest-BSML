#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "HMUI/TextSegmentedControl.hpp"

using namespace TMPro;
using namespace HMUI;
using namespace UnityEngine;
using namespace VRUIControls;
using namespace Zenject;
using namespace GlobalNamespace;

#define CacheNotFoundWarningLog(type) WARNING("Can't find '{}'! (This shouldn't happen and can cause unexpected behaviour)", #type)

namespace BSML::Helpers {
    PhysicsRaycasterWithCache* physicsRaycaster = nullptr;
    PhysicsRaycasterWithCache* GetPhysicsRaycasterWithCache()
    {
        if(!physicsRaycaster)
            physicsRaycaster = Resources::FindObjectsOfTypeAll<MainMenuViewController*>().First()->GetComponent<VRGraphicRaycaster*>()->physicsRaycaster;
        if(!physicsRaycaster)
            CacheNotFoundWarningLog(PhysicsRaycasterWithCache);
        return physicsRaycaster;
    }

    DiContainer* diContainer = nullptr;
    DiContainer* GetDiContainer()
    {
        if(!diContainer)
            diContainer = Resources::FindObjectsOfTypeAll<TextSegmentedControl*>().FirstOrDefault([](TextSegmentedControl* x) { return x->get_transform()->get_parent()->get_name() == "PlayerStatisticsViewController" && x->container; })->container;
        if(!diContainer)
            CacheNotFoundWarningLog(DiContainer);
        return diContainer;
    }

    HoverHintController* hoverHintController;
    HoverHintController* GetHoverHintController() 
    {
        if(!hoverHintController || !Object::IsNativeObjectAlive(hoverHintController))
            hoverHintController = Resources::FindObjectsOfTypeAll<HoverHintController*>().FirstOrDefault();
        if(!hoverHintController)
            CacheNotFoundWarningLog(HoverHintController);
        return hoverHintController;
    }

    TMP_FontAsset* mainTextFont = nullptr;
    TMP_FontAsset* GetMainTextFont() {
        if (!mainTextFont || !Object::IsNativeObjectAlive(mainTextFont))
                    mainTextFont = Resources::FindObjectsOfTypeAll<TMP_FontAsset*>().FirstOrDefault([](auto x){ return x->get_name() == "Teko-Medium SDF"; });
        if(!mainTextFont)
            CacheNotFoundWarningLog(TMP_FontAsset);
        return mainTextFont;
    }

    Material* mainUIFontMaterial = nullptr;
    Material* GetMainUIFontMaterial() {
        if (!mainUIFontMaterial || !Object::IsNativeObjectAlive(mainUIFontMaterial))
            mainUIFontMaterial = Resources::FindObjectsOfTypeAll<Material*>().FirstOrDefault([](auto x){ return x->get_name() == "Teko-Medium SDF Curved Softer"; });
        if(!mainUIFontMaterial)
            CacheNotFoundWarningLog(Material);
        return mainUIFontMaterial;
    }
}