#include "Helpers/utilities.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp" 
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Resources.hpp"

using namespace UnityEngine;

namespace BSML::Utilities {


    template<typename T, typename U>
    using Dictionary = System::Collections::Generic::Dictionary_2<T, U>;

    SafePtr<Dictionary<StringW, UnityEngine::Sprite*>> spriteCache{nullptr};
    Sprite* FindSpriteCached(StringW name) {
        if (!spriteCache)
            spriteCache.emplace(Dictionary<StringW, UnityEngine::Sprite*>::New_ctor());
        
        UnityEngine::Sprite* sprite = nullptr;

        if (spriteCache->TryGetValue(name, byref(sprite)) && sprite)
            return sprite;

        for (auto x : Resources::FindObjectsOfTypeAll<Sprite*>())
        {
            if (x->get_name()->get_Length() == 0)
                continue;
            UnityEngine::Sprite* a = nullptr;
            if(!spriteCache->TryGetValue(x->get_name(), byref(a)) || !a)
                spriteCache->Add(x->get_name(), x);

            if (x->get_name() == name)
                sprite = x;
        }

        return sprite;
    }
}