#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include <map>
#include <string>
#include <functional>
#include <vector>

namespace BSML {
    class BSMLTag;
    class BSMLDocParser;
    
    class BSMLTagParserBase {
        public:
            BSMLTagParserBase(const std::vector<std::string>& aliases);
            virtual ~BSMLTagParserBase();
            
            virtual BSMLTag* newTag() const;
            virtual BSMLTag* parse(const tinyxml2::XMLElement& elem) const;
        protected:
            void ParseChildren(const tinyxml2::XMLElement& elem, BSMLTag* parentTag) const;
            
            friend class BSMLDocParser;
            const std::vector<std::string> aliases;
    };

    template<typename T = BSMLTag>
    requires(std::is_base_of_v<::BSML::BSMLTag, T> || std::is_same_v<::BSML::BSMLTag, T>)
    class BSMLTagParser : BSMLTagParserBase {
        public:
            BSMLTagParser(const std::vector<std::string>& aliases = {"bsml"}) : BSMLTagParserBase(aliases) {}
            virtual BSMLTag* newTag() const override { return new T(); }
    };
}