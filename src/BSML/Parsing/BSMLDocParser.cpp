#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"
#include "logging.hpp"

namespace BSML {
    BSMLDocParser::TagNameToParser BSMLDocParser::tagNameToParser;
    BSMLTagParser* defaultParser = nullptr;

    void BSMLDocParser::RegisterTag(BSMLTagParser* parser) {
        for (auto& alias : parser->aliases) {
            DEBUG("Registering parser for tag {}", alias);
            tagNameToParser[alias] = parser;

            // Get the default bsml parser as a default parser, shortening lookup times later
            if (!defaultParser && alias == "bsml") {
                defaultParser = parser;
            } 
        }

    }

    void BSMLDocParser::UnRegisterTag(BSMLTagParser* parser) {
        for (auto& alias : parser->aliases) {
            auto itr = tagNameToParser.find(alias);
            if (itr != tagNameToParser.end())
                tagNameToParser.erase(itr);
        }
    }

    std::shared_ptr<BSMLTag> BSMLDocParser::parse(std::string_view str) {
        tinyxml2::XMLDocument doc;
        auto error = doc.Parse(str.data());
        if (error != tinyxml2::XML_SUCCESS) {
            ERROR("Error parsing BSML document: {}", tinyxml2::XMLDocument::ErrorIDToName(error));
            std::string validString = fmt::format("<vertical bg='round-rect-panel' pad='5' spacing='4' pref-height='20' vertical-fit='PreferredSize'><text font-size='6' text='ERROR PARSING BSML FILE' align='Center'/><text text='{}' align='Center'/></vertical>", tinyxml2::XMLDocument::ErrorIDToName(error));
            doc.Parse(validString.c_str());
            return parse(doc);
        }
        return parse(doc);
    }

    std::shared_ptr<BSMLTag> BSMLDocParser::parse(const tinyxml2::XMLDocument& doc) {
        INFO("Parsing BSML doc");
        auto parentTag = std::make_shared<BSMLTag>();
        // is this unsafe?
        // sort of
        // does it matter?
        // not if you're using the library as intended
        parentTag->root = parentTag.get();
        parentTag->is_valid = true;

        auto handle = tinyxml2::XMLConstHandle(doc).FirstChildElement();
        auto element = handle.ToElement();
        while(element) {
            auto tag = get_parser(element->Name())->parse(*element);
            parentTag->AddChild(tag);

            handle = handle.NextSiblingElement();
            element = handle.ToElement();
        }

        return parentTag;
    }

    BSMLTagParser* BSMLDocParser::get_parser(std::string alias) {
        auto itr = tagNameToParser.find(alias);
        if (itr == tagNameToParser.end())
            return defaultParser;
        return itr->second;
    } 
}