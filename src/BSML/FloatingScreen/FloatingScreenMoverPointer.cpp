#include "BSML/FloatingScreen/FloatingScreenMoverPointer.hpp"
#include "BSML/FloatingScreen/FloatingScreen.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Input.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Rigidbody.hpp"
#include "UnityEngine/Collider.hpp"

#include <limits>

DEFINE_TYPE(BSML, FloatingScreenMoverPointer);

struct ExtendedRaycastHit : UnityEngine::RaycastHit {
    UnityEngine::Transform get_transform() {
        auto rb = rigidbody;
        if (rb && rb.m_CachedPtr) {
            return rb.transform;
        } else {
            auto col = collider;
            if (col && col.m_CachedPtr) {
                return col.transform;
            } else {
                return UnityEngine::Transform(nullptr);
            }
        }
    }

    __declspec(property(get=get_transform)) UnityEngine::Transform transform;

    UnityEngine::Rigidbody get_rigidbody() {
        auto col = collider;
        return (col && col.m_CachedPtr) ? col.attachedRigidbody : UnityEngine::Rigidbody(nullptr);
    }

    __declspec(property(get=get_rigidbody)) UnityEngine::Rigidbody rigidbody;
};

static_assert(sizeof(UnityEngine::RaycastHit) == sizeof(ExtendedRaycastHit));

inline UnityEngine::Vector3 Vector3Lerp(const UnityEngine::Vector3& a, const UnityEngine::Vector3& b, float t) {
    return {std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t), std::lerp(a.z, b.z, t)};
}

static inline UnityEngine::Quaternion operator* (UnityEngine::Quaternion a, UnityEngine::Quaternion b) {
    return UnityEngine::Quaternion::op_Multiply(a, b);
}

namespace BSML {
    void FloatingScreenMoverPointer::Init(FloatingScreen floatingScreen, VRUIControls::VRPointer pointer) {
        this->floatingScreen = floatingScreen;
        _screenHandle = floatingScreen.handle.transform;
        _realPos = floatingScreen.transform.position;
        _realRot = floatingScreen.transform.rotation;
        _vrPointer = pointer;
    }

    void FloatingScreenMoverPointer::Init(FloatingScreen floatingScreen) {
        auto vrPointer = GetComponent<VRUIControls::VRPointer>();
        Init(floatingScreen, vrPointer);
    }

    void FloatingScreenMoverPointer::Update() {
        auto pointer = _vrPointer;
        if (pointer && pointer.m_CachedPtr && pointer.vrController && pointer.vrController.m_CachedPtr) {
            auto vrController = pointer.vrController;
            if (vrController.triggerValue > 0.9f) {
                if (_grabbingController && _grabbingController.m_CachedPtr) return;
                ExtendedRaycastHit hit;
                if (UnityEngine::Physics::Raycast(vrController.position, vrController.forward, ByRef<UnityEngine::RaycastHit>(&hit), MaxLaserDistance)) {
                    auto t = hit.transform;
                    if (!_screenHandle || t != _screenHandle) return;
                    _grabbingController = vrController;
                    _grabPos = vrController.transform.InverseTransformPoint(floatingScreen.transform.position);
                    _grabRot = UnityEngine::Quaternion::Inverse(vrController.transform.rotation) * floatingScreen.transform.rotation;
                    floatingScreen.OnHandleGrab(pointer);
                }
            }
        }

        // if:
        // - no grabbing controller, or
        // - controller pressed
        // early return
        if (!(_grabbingController && _grabbingController.m_CachedPtr) || _grabbingController.triggerValue > 0.9f) return;

        _grabbingController = nullptr;
        floatingScreen.OnHandleReleased(pointer);

    }

    void FloatingScreenMoverPointer::OnDestroy() {
        internal._vrPointer = nullptr;
        internal._floatingScreen = nullptr;
        internal._screenHandle = nullptr;
        internal._grabbingController = nullptr;
    }

    void FloatingScreenMoverPointer::LateUpdate() {
        if (_grabbingController) {
            float diff = _grabbingController.verticalAxisValue * UnityEngine::Time::get_unscaledDeltaTime();
            if (_grabPos.magnitude > MinScrollDistance) {
                _grabPos.z -= diff;
            } else {
                _grabPos.z -= std::clamp(diff, std::numeric_limits<float>::min(), 0.0f);
            }
            _realPos = _grabbingController.transform.TransformPoint(_grabPos);
            _realRot = _grabbingController.transform.rotation * _grabRot;
        } else return;

        auto t = floatingScreen.transform;
        t.position = Vector3Lerp(t.position, _realPos, 10 * UnityEngine::Time::get_unscaledDeltaTime());
        t.rotation = UnityEngine::Quaternion::Slerp(t.rotation, _realRot, 5 * UnityEngine::Time::get_unscaledDeltaTime());
    }

    FloatingScreen FloatingScreenMoverPointer::__get__floatingScreen() {
        static constexpr auto offset = FloatingScreenMoverPointer::___Base__Size + offsetof(___InternalRepresentation, _floatingScreen);
        return custom_types::read_field<FloatingScreen>(convert(), offset);
    }

    void FloatingScreenMoverPointer::__set__floatingScreen(FloatingScreen value) {
        static constexpr auto offset = FloatingScreenMoverPointer::___Base__Size + offsetof(___InternalRepresentation, _floatingScreen);
        custom_types::write_field<FloatingScreen>(convert(), offset, std::forward(value));
    }
}
