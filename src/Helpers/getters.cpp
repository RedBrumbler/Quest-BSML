#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/LevelCollectionTableView.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "HMUI/TextSegmentedControl.hpp"
#include "HMUI/ScrollView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

using namespace TMPro;
using namespace HMUI;
using namespace UnityEngine;
using namespace VRUIControls;
using namespace Zenject;
using namespace GlobalNamespace;

#define CacheNotFoundWarningLog(type) WARNING("Can't find '{}'! (This shouldn't happen and can cause unexpected behaviour)", #type)

namespace BSML::Helpers {
    SafePtr<UnityEngine::UI::Button> soloButton;
    bool TryGetSoloButton(UnityEngine::UI::Button*& button) {
        if(!soloButton) {
            auto container = GetDiContainer();
            soloButton = container->Resolve<MainMenuViewController*>()->_soloButton;
        }
        if(!soloButton)
            CacheNotFoundWarningLog(PhysicsRaycasterWithCache);

        button = soloButton.ptr();
        return button != nullptr;
    }

    bool TryGetUITextTemplate(TMPro::TextMeshProUGUI*& textMesh) {
        UnityEngine::UI::Button* soloButton;
        if (!TryGetSoloButton(soloButton)) {
            textMesh = nullptr;
            return false;
        }

        textMesh = soloButton->transform->Find("Text")->GetComponent<TMPro::TextMeshProUGUI*>();
        return textMesh;
    }

    SafePtr<PhysicsRaycasterWithCache> physicsRaycaster;
    PhysicsRaycasterWithCache* GetPhysicsRaycasterWithCache()
    {
        if(!physicsRaycaster)
            physicsRaycaster = Resources::FindObjectsOfTypeAll<MainMenuViewController*>()->First()->GetComponent<VRGraphicRaycaster*>()->_physicsRaycaster;
        if(!physicsRaycaster)
            CacheNotFoundWarningLog(PhysicsRaycasterWithCache);
        return physicsRaycaster.ptr();
    }

    SafePtr<DiContainer> diContainer;
    DiContainer* GetDiContainer()
    {
        if(!diContainer)
            diContainer = Resources::FindObjectsOfTypeAll<TextSegmentedControl*>()->FirstOrDefault([](TextSegmentedControl* x) { return x->get_transform()->get_parent()->get_name() == "PlayerStatisticsViewController" && x->_container; })->_container;
        if(!diContainer)
            CacheNotFoundWarningLog(DiContainer);
        return diContainer.ptr();
    }

    SafePtrUnity<HoverHintController> hoverHintController;
    HoverHintController* GetHoverHintController()
    {
        if(!hoverHintController)
            hoverHintController = Resources::FindObjectsOfTypeAll<HoverHintController*>()->FirstOrDefault();
        if(!hoverHintController)
            CacheNotFoundWarningLog(HoverHintController);
        return hoverHintController.ptr();
    }

    SafePtr<IVRPlatformHelper> platformHelper;
    IVRPlatformHelper* GetIVRPlatformHelper()
    {
        if (!platformHelper)
            platformHelper = Resources::FindObjectsOfTypeAll<LevelCollectionTableView*>()->First()->GetComponentInChildren<ScrollView*>()->_platformHelper;
        if (!platformHelper)
            CacheNotFoundWarningLog(IVRPlatformHelper);
        return platformHelper.ptr();
    }

    SafePtrUnity<TMP_FontAsset> mainTextFont;
    TMP_FontAsset* GetMainTextFont() {
        TMPro::TextMeshProUGUI* textMesh;
        if (!mainTextFont && TryGetUITextTemplate(textMesh)) {
            mainTextFont = textMesh->font;
            mainTextFont->boldSpacing = 2.2f;
        }
        if(!mainTextFont)
            CacheNotFoundWarningLog(TMP_FontAsset);
        return mainTextFont.ptr();
    }

    SafePtrUnity<Material> mainUIFontMaterial;
    Material* GetMainUIFontMaterial() {
        TMPro::TextMeshProUGUI* textMesh;
        if (!mainUIFontMaterial && TryGetUITextTemplate(textMesh)) {
            mainUIFontMaterial = textMesh->fontSharedMaterial;
        }
        if(!mainUIFontMaterial)
            CacheNotFoundWarningLog(Material);
        return mainUIFontMaterial.ptr();
    }

    SafePtrUnity<Material> noGlowUIMat;
    Material* GetUINoGlowMat() {
        if (!noGlowUIMat) {
            noGlowUIMat = Resources::FindObjectsOfTypeAll<Material*>()->FirstOrDefault([](auto x){ return x->get_name() == "UINoGlow"; });
        }
        if(!noGlowUIMat)
            CacheNotFoundWarningLog(Material);
        return noGlowUIMat.ptr();
    }

    SafePtrUnity<MainFlowCoordinator> mainFlowCoordinator;
    MainFlowCoordinator* GetMainFlowCoordinator()
    {
        if (!mainFlowCoordinator)
            mainFlowCoordinator = Resources::FindObjectsOfTypeAll<MainFlowCoordinator*>()->FirstOrDefault();
        if(!mainFlowCoordinator)
            CacheNotFoundWarningLog(MainFlowCoordinator);
        return mainFlowCoordinator.ptr();
    }
}
