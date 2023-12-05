#include "BSML/Animations/AnimationControllerData.hpp"
#include "logging.hpp"

#include "Helpers/utilities.hpp"

#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Texture2D.hpp"
#include <chrono>

DEFINE_TYPE(BSML, AnimationControllerData);

namespace BSML {
    AnimationControllerData AnimationControllerData::Make_new(UnityEngine::Texture2D tex, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays) {
        auto self = AnimationControllerData::New_ctor();
        self.animationStateUpdaters = {};

        self._isPlaying = true;
        self.isDelayConsistent = true;
        auto time = std::chrono::system_clock::now();
        auto milis = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
        self.lastSwitch = milis.count();

        self.sprites = ArrayW<UnityEngine::Sprite*>(uvs.size());
        float firstDelay = -1;
        int texWidth = tex.width;
        int texHeight = tex.height;

        for (int i = 0; i < uvs.size(); i++) {
            self.sprites[i] = UnityEngine::Sprite::Create(
                tex,
                UnityEngine::Rect(
                    uvs[i].m_XMin * texWidth,
                    uvs[i].m_YMin * texHeight,
                    uvs[i].m_Width * texWidth,
                    uvs[i].m_Height * texHeight
                ),
                {0, 0},
                100.0f,
                0,
                UnityEngine::SpriteMeshType::Tight,
                {0, 0, 0, 0},
                false
            );

            if (i == 0) {
                firstDelay = delays[i];
            }

            if (delays[i] != firstDelay) {
                self.isDelayConsistent = false;
            }
        }

        self.sprite = Utilities::LoadSpriteFromTexture(tex);
        self.uvs = uvs;
        self.delays = delays;

        return self;
    }

    void AnimationControllerData::dtor() {
        if (sprite && sprite.m_CachedPtr.m_value) {
            UnityEngine::Object::DestroyImmediate(sprite.texture);
            UnityEngine::Object::DestroyImmediate(sprite);
        }

        Finalize();
    }

    ListWrapper<UnityEngine::UI::Image*> AnimationControllerData::get_activeImages() {
        if (!activeImages) {
            activeImages = List<UnityEngine::UI::Image*>::New_ctor();
        }
        return activeImages;
    }

    bool AnimationControllerData::get_isPlaying() {
        return __get__isPlaying();
    }

    void AnimationControllerData::set_isPlaying(bool value) {
        __set__isPlaying(value);
    }

    void AnimationControllerData::CheckFrame(unsigned long long now) {
        if (get_activeImages().size() == 0) return;

        auto diffMs = (now - lastSwitch);
        if (diffMs < delays[uvIndex]) return;
        // VV Bump animations with consistently 10ms or lower frame timings to 100ms
        if (isDelayConsistent && delays[uvIndex] <= 10 && diffMs < 100) return;

        lastSwitch = now;
        do {
            uvIndex++;
            if (uvIndex >= uvs.size()) uvIndex = 0;
        } while (!isDelayConsistent && delays[uvIndex] == 0);

        for (auto image : get_activeImages()) {
            image->set_sprite(sprites[uvIndex]);
        }
    }

    bool AnimationControllerData::IsBeingUsed() {
        return !animationStateUpdaters.empty(); // if no anim updaters exist with this data, it's not being used
    }

    bool AnimationControllerData::Add(AnimationStateUpdater& animationStateUpdater) {
        auto itr = animationStateUpdaters.find(animationStateUpdater);
        if (itr == animationStateUpdaters.end()) {
            animationStateUpdaters.emplace(animationStateUpdater);
            return true;
        } else {
            ERROR("Trying to register {} twice!", fmt::ptr(animationStateUpdater.convert()));
            return false;
        }
    }

    bool AnimationControllerData::Remove(AnimationStateUpdater& animationStateUpdater) {
        auto itr = animationStateUpdaters.find(animationStateUpdater);
        if (itr != animationStateUpdaters.end()) {
            animationStateUpdaters.erase(itr);
            return true;
        } else {
            ERROR("Trying to remove {} twice!", fmt::ptr(animationStateUpdater.convert()));
            return false;
        }

    }
}
