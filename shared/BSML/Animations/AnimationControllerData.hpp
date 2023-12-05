#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/UI/Image.hpp"

namespace BSML {
    class AnimationStateUpdater;
}

DECLARE_CLASS_CORDL(BSML, AnimationControllerData, bs_hook::Il2CppWrapperType,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(UnityEngine::Sprite, sprite);
        DECLARE_INSTANCE_FIELD(int, uvIndex);
        DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Rect>, uvs);
        DECLARE_INSTANCE_FIELD(ArrayW<float>, delays);
        DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Sprite>, sprites);
        DECLARE_INSTANCE_FIELD(UnityEngine::Material, animMaterial);
        DECLARE_INSTANCE_FIELD(bool, isDelayConsistent);
        DECLARE_INSTANCE_FIELD(ListWrapper<UnityEngine::UI::Image>, activeImages);
        DECLARE_INSTANCE_FIELD(bool, _isPlaying);

        private:
            unsigned long long lastSwitch;
            std::set<Il2CppObject*> animationStateUpdaters;
    );

    FIELD_ACCESSOR(sprite);
    FIELD_ACCESSOR(uvIndex);
    FIELD_ACCESSOR(uvs);
    FIELD_ACCESSOR(delays);
    FIELD_ACCESSOR(sprites);
    FIELD_ACCESSOR(animMaterial);
    FIELD_ACCESSOR(isDelayConsistent);
    FIELD_ACCESSOR(activeImages);
    FIELD_ACCESSOR(_isPlaying);
    FIELD_ACCESSOR(lastSwitch);
    FIELD_ACCESSOR(animationStateUpdaters);

    DECLARE_INSTANCE_METHOD(ListWrapper<UnityEngine::UI::Image>, get_activeImages);

    DECLARE_INSTANCE_METHOD(bool, IsBeingUsed);

    DECLARE_INSTANCE_METHOD(bool, get_isPlaying);
    DECLARE_INSTANCE_METHOD(void, set_isPlaying, bool value);

    DECLARE_DEFAULT_CTOR();
    DECLARE_DTOR(dtor);
    public:
        bool Add(AnimationStateUpdater& animationStateUpdater);
        bool Remove(AnimationStateUpdater& animationStateUpdater);

        static AnimationControllerData Make_new(UnityEngine::Texture2D tex, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays);
        void CheckFrame(unsigned long long now);

)
