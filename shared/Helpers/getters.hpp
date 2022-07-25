#pragma once

#include "VRUIControls/PhysicsRaycasterWithCache.hpp"
#include "Zenject/DiContainer.hpp"

namespace BSML::Helpers {
    VRUIControls::PhysicsRaycasterWithCache* GetPhysicsRaycasterWithCache();
    Zenject::DiContainer* GetDiContainer();
}