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

            // only the root BSML tag is a shared ptr, the rest are all regular c pointers.
            // memory management is done by BSML, so you don't need to worry about it.
            static std::shared_ptr<BSMLTag> parse(std::string_view str);
            static std::shared_ptr<BSMLTag> parse(const tinyxml2::XMLDocument& doc);
            static BSMLTagParser* get_parser(std::string alias);

        private:
            using TagNameToParser = std::map<std::string, BSMLTagParser*>;
            static TagNameToParser tagNameToParser;
    };
}