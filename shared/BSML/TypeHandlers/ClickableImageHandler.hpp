#pragma once

#include "TypeHandler.hpp"
#include "../Components/ClickableImage.hpp"

namespace BSML {
    class ClickableImageHandler : public TypeHandler<BSML::ClickableImage> {
        public:
            using Base = TypeHandler<BSML::ClickableImage>;
            ClickableImageHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;

            virtual void HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override;
    };
}
