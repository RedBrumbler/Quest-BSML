#pragma once

#include "BSML/Macros/BSMLMacro.hpp"

namespace BSML {
    class RepeatMacro : public BSMLMacro {
        public:
            PropMap get_props() const override;
            void Execute(UnityEngine::Transform* parent, const std::map<std::string, std::string>& data, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const override;
    };
}