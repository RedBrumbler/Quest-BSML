#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "UnityEngine/UI/Image.hpp"

namespace BSML {
    class ImageHandler : public TypeHandler<UnityEngine::UI::Image*> {
        public:
            using Base = TypeHandler<UnityEngine::UI::Image*>;
            ImageHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}