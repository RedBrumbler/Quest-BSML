#include "BSML/ComponentTypeWithData.hpp"

namespace BSML {
    std::map<std::string, std::string> ComponentTypeWithData::GetParameters(const std::map<std::string, std::string>& allParams, const std::map<std::string, std::vector<std::string>>& props) {
        std::map<std::string, std::string> result;
        for (const auto& [prop, vec] : props) {
            for (const auto& alias : vec) {
                auto itr = allParams.find(alias);
                if (itr == allParams.end()) continue;

                result[prop] = itr->second;    
                break;
            }
        }

        return result;
    }
}