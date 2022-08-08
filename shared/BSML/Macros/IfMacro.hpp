#pragma once

#include "BSMLMacro.hpp"

namespace BSML {
    class IfMacro : public BSMLMacro {
        public:
            PropMap get_props() const override;
            void Execute(UnityEngine::Transform* parent, const std::map<std::string, std::string>& data, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const override;
    };
}