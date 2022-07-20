#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include <map>
#include <string>

namespace BSML {
    class BSMLTag;
    class BSMLTagParser;

    class BSMLDocParser {
        public:
            static void RegisterTag(BSMLTagParser* parser);
            static void UnRegisterTag(BSMLTagParser* parser);

            static BSMLTag* parse(std::string_view str);
            static BSMLTag* parse(const tinyxml2::XMLDocument& doc);
            static BSMLTagParser* get_parser(std::string alias);

        private:
            using TagNameToParser = std::map<std::string, BSMLTagParser*>;
            static TagNameToParser tagNameToParser;
    };
}