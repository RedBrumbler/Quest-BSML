#pragma once

#include "TypeHandler.hpp"
#include "UnityEngine/UI/RawImage.hpp"

namespace BSML {
    class RawImageHandler : public TypeHandler<UnityEngine::UI::RawImage*> {
        public:
            using Base = TypeHandler<UnityEngine::UI::RawImage*>;
            RawImageHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}