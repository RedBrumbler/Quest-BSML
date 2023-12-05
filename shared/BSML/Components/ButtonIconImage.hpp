#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Sprite.hpp"

DECLARE_CLASS_CORDL(BSML, ButtonIconImage, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image, image);
    );

    FIELD_ACCESSOR(image);

    public:
        void SetIcon(StringW path);
        void SetIcon(UnityEngine::Sprite sprite);
        UnityEngine::Sprite get_Icon();
        void set_Icon(UnityEngine::Sprite icon);
        __declspec(property(get=get_Icon,put=set_Icon)) UnityEngine::Sprite Icon;
)
