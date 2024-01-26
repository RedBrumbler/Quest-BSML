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
    UnityEngine::Transform* get_transform() {
        auto rb = get_rigidbody();
        if (rb && rb->m_CachedPtr) {
            return rb->get_transform();
        } else {
            auto col = get_collider();
            if (col && col->m_CachedPtr) {
                return col->get_transform();
            } else {
                return nullptr;
            }
        }
    }

    UnityEngine::Rigidbody* get_rigidbody() {
        auto col = get_collider();
        return (col && col->m_CachedPtr) ? col->get_attachedRigidbody() : nullptr;
    }
};

static_assert(sizeof(UnityEngine::RaycastHit) == sizeof(ExtendedRaycastHit));

inline UnityEngine::Vector3 Vector3Lerp(const UnityEngine::Vector3& a, const UnityEngine::Vector3& b, float t) {
    return {std::lerp(a.x, b.x, t), std::lerp(a.y, b.y, t), std::lerp(a.z, b.z, t)};
}

static inline UnityEngine::Quaternion operator*(UnityEngine::Quaternion a, UnityEngine::Quaternion b) {
    return UnityEngine::Quaternion::op_Multiply(a, b);
}

namespace BSML {
    void FloatingScreenMoverPointer::Init(FloatingScreen* floatingScreen, VRUIControls::VRPointer* pointer) {
        _floatingScreen = floatingScreen;
        _screenHandle = floatingScreen->handle->get_transform();
        _realPos = floatingScreen->get_transform()->get_position();
        _realRot = floatingScreen->get_transform()->get_rotation();
        _vrPointer = pointer;
    }

    void FloatingScreenMoverPointer::Init(FloatingScreen* floatingScreen) {
        auto vrPointer = GetComponent<VRUIControls::VRPointer*>();
        Init(floatingScreen, vrPointer);
    }

    void FloatingScreenMoverPointer::Update() {
        auto pointer = _vrPointer;
        auto vrController = pointer && pointer->m_CachedPtr ? pointer->lastSelectedVrController : nullptr;
        if (vrController && vrController->m_CachedPtr) {
            if (vrController->get_triggerValue() > 0.9f) {
                if (_grabbingController && _grabbingController->m_CachedPtr) return;
                ExtendedRaycastHit hit;
                if (UnityEngine::Physics::Raycast(vrController->_viewAnchorTransform->get_position(), vrController->_viewAnchorTransform->get_forward(), ByRef<UnityEngine::RaycastHit>(&hit), MaxLaserDistance)) {
                    auto t = hit.get_transform();
                    if (!_screenHandle || t != _screenHandle) return;
                    _grabbingController = vrController;
                    _grabPos = vrController->_viewAnchorTransform->InverseTransformPoint(_floatingScreen->get_transform()->get_position());
                    _grabRot = UnityEngine::Quaternion::Inverse(vrController->_viewAnchorTransform->get_rotation()) * _floatingScreen->get_transform()->get_rotation();
                    _floatingScreen->OnHandleGrab(pointer);
                }
            }
        }

        // if:
        // - no grabbing controller, or
        // - controller pressed
        // early return
        if (!(_grabbingController && _grabbingController->m_CachedPtr) || _grabbingController->get_triggerValue() > 0.9f) return;

        _grabbingController = nullptr;
        _floatingScreen->OnHandleReleased(pointer);
    }

    void FloatingScreenMoverPointer::OnDestroy() {
        _vrPointer = nullptr;
        _floatingScreen = nullptr;
        _screenHandle = nullptr;
        _grabbingController = nullptr;
    }

    void FloatingScreenMoverPointer::LateUpdate() {
        if (_grabbingController) {
            float diff = -_grabbingController->thumbstick.y * UnityEngine::Time::get_unscaledDeltaTime();
            if (_grabPos.get_magnitude() > MinScrollDistance) {
                _grabPos.z -= diff;
            } else {
                _grabPos.z -= std::clamp(diff, std::numeric_limits<float>::min(), 0.0f);
            }
            _realPos = _grabbingController->_viewAnchorTransform->get_transform()->TransformPoint(_grabPos);
            _realRot = _grabbingController->_viewAnchorTransform->get_transform()->get_rotation() * _grabRot;
        } else return;

        _floatingScreen->get_transform()->set_position(Vector3Lerp(_floatingScreen->get_transform()->get_position(), _realPos, 10 * UnityEngine::Time::get_unscaledDeltaTime()));
        _floatingScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Slerp(_floatingScreen->get_transform()->get_rotation(), _realRot, 5 * UnityEngine::Time::get_unscaledDeltaTime()));
    }
}
