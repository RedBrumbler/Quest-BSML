#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Parsing/BSMLNodeParser.hpp"
#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Tags/BSMLTag.hpp"
#include "logging.hpp"


namespace BSML {
    BSMLDocParser::TagNameToParser __attribute__((init_priority(200))) BSMLDocParser::tagNameToParser;
    BSMLNodeParserBase* defaultParser = nullptr;

    void BSMLDocParser::RegisterTag(BSMLNodeParserBase* parser) {
        for (auto& alias : parser->aliases) {
            DEBUG("Registering parser {} for tag {}", fmt::ptr(parser), alias);
            tagNameToParser.emplace(alias, parser);

            // Get the default bsml parser as a default parser, shortening lookup times later
            if (!defaultParser && alias == "bsml") {
                defaultParser = parser;
            } 
        }

    }

    void BSMLDocParser::UnRegisterTag(BSMLNodeParserBase* parser) {
        for (auto& alias : parser->aliases) {
            auto itr = tagNameToParser.find(alias);
            if (itr != tagNameToParser.end())
                tagNameToParser.erase(itr);
        }
    }

    BSMLNodeParserBase* BSMLDocParser::get_parser(std::string alias) {
        auto itr = tagNameToParser.find(alias);
        if (itr == tagNameToParser.end())
            return defaultParser;
        return itr->second;
    }
}