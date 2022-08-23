#include "BSML/Animations/AnimationController.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include <chrono>

DEFINE_TYPE(BSML, AnimationController);

namespace BSML {
    SafePtrUnity<AnimationController> AnimationController::instance;
    AnimationController* AnimationController::get_instance() {
        if (!instance) {
            instance = UnityEngine::GameObject::New_ctor()->AddComponent<AnimationController*>();
            instance->get_gameObject()->set_name("AnimationController");
            UnityEngine::Object::DontDestroyOnLoad(instance->get_gameObject());
        }
        return instance.ptr();
    }

    void AnimationController::ctor() {
        registeredAnimations = StringToAnimDataDictionary::New_ctor();
    }

    AnimationControllerData* AnimationController::Register(StringW key, UnityEngine::Texture2D* texture, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays) {
        DEBUG("Registering {}", key);
        Il2CppObject* animationData = nullptr;
        if (!registeredAnimations->TryGetValue(key, byref(animationData))) {
            animationData = AnimationControllerData::Make_new(texture, uvs, delays);
            registeredAnimations->Add(key, animationData);
        } else {
            INFO("key {} was already registered, destroying texture and returning", key);
            UnityEngine::Object::Destroy(texture);
        }
        return reinterpret_cast<AnimationControllerData*>(animationData);
    }

    void AnimationController::InitializeLoadingAnimation() {
        // /shrug
    }

    void AnimationController::Update() {
        auto time = std::chrono::system_clock::now();
        auto milis = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
        auto now = milis.count();
        auto enumerator = registeredAnimations->GetEnumerator();
        while (enumerator.MoveNext()) {
            auto current = reinterpret_cast<AnimationControllerData*>(enumerator.get_Current().get_Value());
            if (current->get_isPlaying()) {
                current->CheckFrame(now);
            }
        }
    }
}