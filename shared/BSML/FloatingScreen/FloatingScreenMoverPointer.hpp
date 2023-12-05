#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/MeshRenderer.hpp"

#include "VRUIControls/VRPointer.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "GlobalNamespace/FirstPersonFlyingController.hpp"

namespace BSML {
    class FloatingScreen;
}

DECLARE_CLASS_CORDL(BSML, FloatingScreenMoverPointer, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(VRUIControls::VRPointer, _vrPointer);
        DECLARE_INSTANCE_FIELD(UnityEngine::Transform, _screenHandle);
        DECLARE_INSTANCE_FIELD(GlobalNamespace::VRController, _grabbingController);
        DECLARE_INSTANCE_FIELD(UnityEngine::Vector3, _grabPos);
        DECLARE_INSTANCE_FIELD(UnityEngine::Quaternion, _grabRot);
        DECLARE_INSTANCE_FIELD(UnityEngine::Vector3, _realPos);
        DECLARE_INSTANCE_FIELD(UnityEngine::Quaternion, _realRot);
        DECLARE_INSTANCE_FIELD(bs_hook::Il2CppWrapperType, _floatingScreen);
    );

    FIELD_ACCESSOR(_vrPointer);
    FIELD_ACCESSOR(_screenHandle);
    FIELD_ACCESSOR(_grabbingController);
    FIELD_ACCESSOR(_grabPos);
    FIELD_ACCESSOR(_grabRot);
    FIELD_ACCESSOR(_realPos);
    FIELD_ACCESSOR(_realRot);

    protected:
    FloatingScreen __get__floatingScreen();
    void __set__floatingScreen(FloatingScreen value);
    __declspec(property(get=__get__floatingScreen, put=__set__floatingScreen)) FloatingScreen floatingScreen;

    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, LateUpdate);
    public:
        void Init(FloatingScreen floatingScreen, VRUIControls::VRPointer pointer);
        void Init(FloatingScreen floatingScreen);

        static constexpr const float MinScrollDistance = 0.25f;
        static constexpr const float MaxLaserDistance = 50.0f;
)
