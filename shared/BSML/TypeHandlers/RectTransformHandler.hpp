#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace BSML {
    class RectTransformHandler : public TypeHandler<UnityEngine::RectTransform*> {
        public:
            using Base = TypeHandler<UnityEngine::RectTransform*>;
            RectTransformHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}