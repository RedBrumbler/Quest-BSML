#pragma once

#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

namespace BSML {
    class ContentSizeFitterHandler : public TypeHandler<UnityEngine::UI::ContentSizeFitter*> {
        public:
            using Base = TypeHandler<UnityEngine::UI::ContentSizeFitter*>;
            ContentSizeFitterHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}