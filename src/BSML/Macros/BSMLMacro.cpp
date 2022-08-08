#include "BSML/Macros/BSMLMacro.hpp"

namespace BSML {
    BSMLMacro::BSMLMacro() : BSMLNode() {
        #if MAKE_DOCS
        nodeType = NodeType::Macro;
        #endif
    };

    const BSMLMacro::PropMap& BSMLMacro::get_cachedProps() const {
        if (cachedProps.empty())
            const_cast<BSMLMacro*>(this)->cachedProps = get_props();
        return cachedProps;
    }

    void BSMLMacro::Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const {
        std::map<std::string, std::string> data;
        for (const auto& [key, aliases] : get_cachedProps()) {
            for (const auto& alias : aliases) {
                auto itr = attributes.find(alias);
                if (itr != attributes.end()) {
                    data[key] = itr->second;
                }
            }
        }

        Execute(parent, data, parserParams, componentInfo);
    }
}