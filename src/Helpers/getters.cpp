#include "Helpers/getters.hpp"
#include "logging.hpp"
#include "hooking.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/HealthWarningViewController.hpp"
#include "GlobalNamespace/LevelCollectionTableView.hpp"
#include "GlobalNamespace/MainSettingsMenuViewControllersInstaller.hpp"
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
    SafePtrUnity<TMPro::TextMeshProUGUI> soloButtonTextMesh;
    bool TryGetSoloButtonTextMesh(TMPro::TextMeshProUGUI*& textMesh)
    {
        if(!soloButtonTextMesh) {
            auto vc = UnityEngine::Resources::FindObjectsOfTypeAll<MainMenuViewController*>();
            if (vc->get_Length() != 0) {
                auto transform = vc->First()->_soloButton->transform;
                auto text = transform->Find("Text");
                textMesh = text->GetComponent<TMPro::TextMeshProUGUI *>();
                return textMesh;
            }
            if(!soloButtonTextMesh)
                CacheNotFoundWarningLog(soloButtonTextMesh);
        }
        if (soloButtonTextMesh)
            textMesh = soloButtonTextMesh.ptr();
        return soloButtonTextMesh;
    }

    SafePtrUnity<TMPro::TextMeshProUGUI> healthAndSafetyTextMesh;
    bool TryGetHealthAndSafetyTextMesh(TMPro::TextMeshProUGUI*& textMesh)
    {
        if(!healthAndSafetyTextMesh) {
            auto vc = UnityEngine::Resources::FindObjectsOfTypeAll<HealthWarningViewController*>();
            if (vc->get_Length() != 0)
                healthAndSafetyTextMesh = vc->First()->_healthAndSafetyTextMesh;
            if(!healthAndSafetyTextMesh)
                CacheNotFoundWarningLog(HealthAndSafetyTextMesh);
        }
        if (healthAndSafetyTextMesh)
            textMesh = healthAndSafetyTextMesh.ptr();
        return healthAndSafetyTextMesh;
    }

    bool TryGetUITextTemplate(TMPro::TextMeshProUGUI *&textMesh)
    {
        textMesh = nullptr;
        if (TryGetSoloButtonTextMesh(textMesh))
            return true;
        if (TryGetHealthAndSafetyTextMesh(textMesh))
            return true;
        return false;
    }

    SafePtr<PhysicsRaycasterWithCache> physicsRaycaster;
    PhysicsRaycasterWithCache *GetPhysicsRaycasterWithCache()
    {
        if (physicsRaycaster)
            return physicsRaycaster.ptr();

        if (!physicsRaycaster) {
            auto vc = Resources::FindObjectsOfTypeAll<MainMenuViewController *>();
            if (vc->get_Length() != 0) {
                auto raycaster = vc->First()->GetComponent<VRGraphicRaycaster *>();
                if (raycaster)
                    physicsRaycaster = raycaster->_physicsRaycaster;
            }
        }
        if (!physicsRaycaster) {
            auto vc = Resources::FindObjectsOfTypeAll<HealthWarningViewController *>();
            if (vc->get_Length() != 0) {
                auto raycaster = vc->First()->GetComponent<VRGraphicRaycaster *>();
                if (raycaster)
                    physicsRaycaster = raycaster->_physicsRaycaster;
            }
        }
        if(!physicsRaycaster)
            CacheNotFoundWarningLog(PhysicsRaycasterWithCache);
        return physicsRaycaster.ptr();
    }

    SafePtr<DiContainer> diContainer;
    DiContainer* GetDiContainer() {
        if(!diContainer)
            diContainer = Resources::FindObjectsOfTypeAll<TextSegmentedControl*>()->FirstOrDefault([](TextSegmentedControl* x) { return x->get_transform()->get_parent()->get_name() == "PlayerStatisticsViewController" && x->_container; })->_container;
        if(!diContainer)
            CacheNotFoundWarningLog(DiContainer);
        return diContainer.ptr();
    }

    SafePtrUnity<HoverHintController> hoverHintController;
    HoverHintController* GetHoverHintController() {
        if(!hoverHintController)
            hoverHintController = Resources::FindObjectsOfTypeAll<HoverHintController*>()->FirstOrDefault();
        if(!hoverHintController)
            CacheNotFoundWarningLog(HoverHintController);
        return hoverHintController.ptr();
    }

    SafePtr<IVRPlatformHelper> platformHelper;
    IVRPlatformHelper* GetIVRPlatformHelper() {
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
    MainFlowCoordinator* GetMainFlowCoordinator() {
        if (!mainFlowCoordinator)
            mainFlowCoordinator = Resources::FindObjectsOfTypeAll<MainFlowCoordinator*>()->FirstOrDefault();
        if(!mainFlowCoordinator)
            CacheNotFoundWarningLog(MainFlowCoordinator);
        return mainFlowCoordinator.ptr();
    }
}

MAKE_AUTO_HOOK_MATCH(
    MainSettingsMenuViewControllersInstaller_InstallBindings,
    &GlobalNamespace::MainSettingsMenuViewControllersInstaller::InstallBindings,
    void,
    GlobalNamespace::MainSettingsMenuViewControllersInstaller* self
) {
    BSML::Helpers::diContainer = self->get_Container();
    MainSettingsMenuViewControllersInstaller_InstallBindings(self);
}
