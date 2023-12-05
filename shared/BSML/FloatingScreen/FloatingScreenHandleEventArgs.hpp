#pragma once

#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"

namespace BSML {
    struct FloatingScreenHandleEventArgs {
        FloatingScreenHandleEventArgs(::VRUIControls::VRPointer vrPointer, UnityEngine::Vector3 position, UnityEngine::Quaternion rotation) : vrPointer(vrPointer), position(position), rotation(rotation) {}
        const SafePtrUnity<::VRUIControls::VRPointer> vrPointer;
        const UnityEngine::Vector3 position;
        const UnityEngine::Quaternion rotation;

        bool operator==(const FloatingScreenHandleEventArgs& other) const {
            return other.position == position && other.rotation == rotation;
        }

        bool operator!=(const FloatingScreenHandleEventArgs& other) const {
            return !(*this == other);
        }
    };
}
