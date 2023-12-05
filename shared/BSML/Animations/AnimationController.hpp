#pragma once

#include "custom-types/shared/macros.hpp"
#include "AnimationControllerData.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Rect.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/IReadOnlyDictionary_2.hpp"

DECLARE_CLASS_CORDL(BSML, AnimationController, UnityEngine::MonoBehaviour,
    using StringToAnimDataDictionary = System::Collections::Generic::Dictionary_2<StringW, bs_hook::Il2CppWrapperType>;
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(AnimationControllerData, loadingAnimation);
        DECLARE_INSTANCE_FIELD(StringToAnimDataDictionary, registeredAnimations);
    );

    FIELD_ACCESSOR(loadingAnimation);
    FIELD_ACCESSOR(registeredAnimations);

    DECLARE_INSTANCE_METHOD(void, InitializeLoadingAnimation);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(AnimationControllerData, Register, StringW key, UnityEngine::Texture2D texture, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays);

    public:
        bool TryGetAnimationControllerData(StringW key, AnimationControllerData& out);
        bool Unregister(StringW key);
        bool CanUnregister(AnimationControllerData animationData);
        static AnimationController get_instance();
        DECLARE_CTOR(ctor);
    protected:
        static SafePtrUnity<AnimationController> instance;
)
