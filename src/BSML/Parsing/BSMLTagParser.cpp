#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"
#include "logging.hpp"


namespace BSML {
    BSMLTagParserBase::BSMLTagParserBase(const std::vector<std::string>& aliases) : aliases(aliases) {
        BSMLDocParser::RegisterTag(this);
    }

    BSMLTagParserBase::~BSMLTagParserBase() {
        BSMLDocParser::UnRegisterTag(this);
    }
    
    BSMLTag* BSMLTagParserBase::newTag() const {
        return new BSMLTag();
    }

    BSMLTag* BSMLTagParserBase::parse(const tinyxml2::XMLElement& elem) const {
        auto tag = newTag();
        tag->parse(elem);
        
        ParseChildren(elem, tag);
        
        return tag;
    }

    void BSMLTagParserBase::ParseChildren(const tinyxml2::XMLElement& elem, BSMLTag* parentTag) const {
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