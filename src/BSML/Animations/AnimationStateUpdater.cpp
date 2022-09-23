#include "BSML/Animations/AnimationStateUpdater.hpp"

DEFINE_TYPE(BSML, AnimationStateUpdater);

namespace BSML {
    AnimationControllerData* AnimationStateUpdater::get_controllerData() {
        return controllerData;
    }

    void AnimationStateUpdater::set_controllerData(AnimationControllerData* value) {
        if (controllerData) {
            OnDisable();
            controllerData->RemoveUpdater(this);
        }
        controllerData = value;
        controllerData->AddUpdater(this);
        if (get_isActiveAndEnabled()) {
            OnEnable();
        }
    }

    void AnimationStateUpdater::OnEnable() {
        if (controllerData && image) {
            controllerData->Add(image);
        }
    }

    void AnimationStateUpdater::OnDisable() {
        if (controllerData && image) {
            controllerData->Remove(image);
        }
    }

    void AnimationStateUpdater::OnDestroy() {
        if (controllerData && image) {
            controllerData->Remove(image);
            controllerData->RemoveUpdater(this);
        }
    }
}