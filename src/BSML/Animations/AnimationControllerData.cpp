#include "BSML/Animations/AnimationControllerData.hpp"
#include "BSML/Animations/AnimationController.hpp"

#include "Helpers/utilities.hpp"

#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Texture2D.hpp"
#include <chrono>

DEFINE_TYPE(BSML, AnimationControllerData);


namespace BSML {
    AnimationControllerData* AnimationControllerData::Make_new(StringW key, UnityEngine::Texture2D* tex, ArrayW<UnityEngine::Rect> uvs, ArrayW<float> delays) {
        auto self = AnimationControllerData::New_ctor();
        self->key = key;
        self->_isPlaying = true;
        self->isDelayConsistent = true;
        self->autoDestructible = true;
        auto time = std::chrono::system_clock::now();
        auto milis = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
        self->lastSwitch = milis.count();

        self->sprites = ArrayW<UnityEngine::Sprite*>(uvs.size());
        float firstDelay = -1;
        int texWidth = tex->get_width();
        int texHeight = tex->get_height();

        for (int i = 0; i < uvs.size(); i++) {
            self->sprites[i] = UnityEngine::Sprite::Create(
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
                self->isDelayConsistent = false;
            }
        }

        self->sprite = Utilities::LoadSpriteFromTexture(tex);
        self->uvs = uvs;
        self->delays = delays;

        return self;
    }

    ListWrapper<UnityEngine::UI::Image*> AnimationControllerData::get_activeImages() {
        if (!activeImages) {
            activeImages = List<UnityEngine::UI::Image*>::New_ctor();
        }
        return activeImages;
    }

    ListWrapper<Il2CppObject*> AnimationControllerData::get_updaters() {
        if (!updaters) {
            updaters = List<Il2CppObject*>::New_ctor();
        }
        return updaters;
    }

    void AnimationControllerData::Add(UnityEngine::UI::Image* image) {
        get_activeImages()->Add(image);
    }

    void AnimationControllerData::AddUpdater(Il2CppObject* updater) {
        get_updaters()->Add(updater);
    }

    void AnimationControllerData::Remove(UnityEngine::UI::Image* image) {
        get_activeImages()->Remove(image);
    }

    void AnimationControllerData::RemoveUpdater(Il2CppObject* updater) {
        get_updaters()->Remove(updater);
        if (get_updaters().size() == 0 && autoDestructible) {
            // unregister self from anim control, there are no gifs left that use this data
            // we know this because the updaters list is updated when the data is changed.
            // FIXME: what if someone swaps controller data manually? then this will cause issues! probably tell them to use autoDestructible = false temporarily or something?
            BSML::AnimationController::get_instance()->Unregister(key);
        }
    }

    bool AnimationControllerData::get_isPlaying() {
        return _isPlaying;
    }

    void AnimationControllerData::set_isPlaying(bool value) {
        _isPlaying = value;
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
}