#pragma once

#include "BSML/Parsing/BSMLParserParams.hpp"
#include "tinyxml2/shared/tinyxml2.h"
#include <map>
#include <string>

namespace BSML {
    class BSMLNode;
    class BSMLNodeParserBase;
    class BSMLDocParser {
        public:
            static void RegisterTag(BSMLNodeParserBase* parser);
            static void UnRegisterTag(BSMLNodeParserBase* parser);

            static BSMLNodeParserBase* get_parser(std::string alias);
        private:
            using TagNameToParser = std::map<std::string, BSML::BSMLNodeParserBase*>;
            static TagNameToParser tagNameToParser;
    };
}