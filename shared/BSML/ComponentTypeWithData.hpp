#pragma once

#include "UnityEngine/Component.hpp"
#include "Parsing/BSMLParserParams.hpp"
#include <string>
#include <map>

namespace BSML {
    class TypeHandlerBase;
    struct ComponentTypeWithData {
        public:
            TypeHandlerBase* typeHandler;
            UnityEngine::Component component;
            std::map<std::string, std::string> data;

        static std::map<std::string, std::string> GetParameters(const std::map<std::string, std::string>& allParams, const BSMLParserParams& parserParams, const std::map<std::string, std::vector<std::string>>& props);
    };
}
