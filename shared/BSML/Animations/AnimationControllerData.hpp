#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/UI/Image.hpp"

DECLARE_CLASS_CODEGEN(BSML, AnimationControllerData, Il2CppObject,
    DECLARE_INSTANCE_FIELD(StringW, key);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, sprite);
    DECLARE_INSTANCE_FIELD(int, uvIndex);
    DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Rect>, uvs);
    DECLARE_INSTANCE_FIELD(ArrayW<float>, delays);
    DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Sprite*>, sprites);
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, animMaterial);
    DECLARE_INSTANCE_FIELD(bool, isDelayConsistent);
    DECLARE_INSTANCE_FIELD(bool, autoDestructible);
    DECLARE_INSTANCE_FIELD(List<UnityEngine::UI::Image*>*, activeImages);
    DECLARE_INSTANCE_FIELD(List<Il2CppObject*>*, updaters);
    DECLARE_INSTANCE_METHOD(ListWrapper<UnityEngine::UI::Image*>, get_activeImages);
    DECLARE_INSTANCE_METHOD(ListWrapper<Il2CppObject*>, get_updaters);
    DECLARE_INSTANCE_METHOD(void, Add, UnityEngine::UI::Image* image);
    DECLARE_INSTANCE_METHOD(void, AddUpdater, Il2CppObject* updater);
    DECLARE_INSTANCE_METHOD(void, Remove, UnityEngine::UI::Image* image);
    DECLARE_INSTANCE_METHOD(void, RemoveUpdater, Il2CppObject* updater);

    DECLARE_INSTANCE_FIELD(bool, _isPlaying);
    DECLARE_INSTANCE_METHOD(bool, get_isPlaying);
    DECLARE_INSTANCE_METHOD(void, set_isPlaying, bool value);

    DECLARE_DEFAULT_CTOR();
    public:
        static AnimationControllerData* Make_new(StringW key, UnityEngine::Texture2D* tex, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays);
        void CheckFrame(unsigned long long now);
    private:
        unsigned long long lastSwitch;
)