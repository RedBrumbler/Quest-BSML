#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"
#include "logging.hpp"

namespace BSML {
    BSMLTagParser BSMLTagParser::bsmlTagParser;

    BSMLTagParser::BSMLTagParser(std::vector<std::string> aliases) : aliases(aliases) {
        BSMLDocParser::RegisterTag(this);
    }

    BSMLTagParser::~BSMLTagParser() {
        BSMLDocParser::UnRegisterTag(this);
    }
    
    BSMLTag* BSMLTagParser::newTag() {
        return new BSMLTag();
    }

    BSMLTag* BSMLTagParser::parse(const tinyxml2::XMLElement& elem) {
        auto tag = newTag();
        tag->parse(elem);
        
        ParseChildren(elem, tag);
        
        return tag;
    }

    void BSMLTagParser::ParseChildren(const tinyxml2::XMLElement& elem, BSMLTag* parentTag) {
        auto handle = tinyxml2::XMLConstHandle(elem).FirstChildElement();
        for (
            const tinyxml2::XMLElement* element = nullptr;
            (element = handle.ToElement()) != nullptr;
            handle = handle.NextSiblingElement()
        ) {
            parentTag->AddChild(BSMLDocParser::get_parser(element->Name())->parse(*element));
        }
    }
}