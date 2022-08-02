#pragma once

#include "BSML/Parsing/BSMLNode.hpp"

namespace BSML {
    class BSMLMacro : public BSMLNode {
        public:
            BSMLMacro() : BSMLNode() {};

            virtual void Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const override;
        private:
    };
}