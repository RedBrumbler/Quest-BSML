#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include <map>
#include <string>
#include <functional>
#include <vector>

namespace BSML {
    class BSMLTag;
    class BSMLDocParser;
    
    class BSMLTagParser {
        public:
            BSMLTagParser(std::vector<std::string> aliases = {"bsml"});
            virtual ~BSMLTagParser();
            
            virtual BSMLTag* newTag();
            virtual BSMLTag* parse(const tinyxml2::XMLElement& elem);
        protected:
            static BSMLTagParser bsmlTagParser;
            void ParseChildren(const tinyxml2::XMLElement& elem, BSMLTag* parentTag);
            
            friend class BSMLDocParser;
            std::vector<std::string> aliases;
    };
}