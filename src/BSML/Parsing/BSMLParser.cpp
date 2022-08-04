#include "BSML/Parsing/BSMLParser.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Parsing/BSMLNodeParser.hpp"
#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "logging.hpp"

namespace BSML {
    BSMLParser::BSMLParser() : root(new BSMLNode()), parserParams(std::make_shared<BSMLParserParams>()) {}
    BSMLParser::~BSMLParser() {
        delete root;
    }

    std::shared_ptr<BSMLParser> BSMLParser::parse(std::string_view str) {
        auto parser = std::make_shared<BSMLParser>();
        tinyxml2::XMLDocument doc;
        auto error = doc.Parse(str.data());
        if (error != tinyxml2::XML_SUCCESS) {
            ERROR("Error parsing BSML document: {}", tinyxml2::XMLDocument::ErrorIDToName(error));
            std::string validString = fmt::format("<vertical bg='round-rect-panel' pad='5' spacing='4' pref-height='20' vertical-fit='PreferredSize'><text font-size='6' text='ERROR PARSING BSML FILE' align='Center'/><text text='{}' align='Center'/></vertical>", tinyxml2::XMLDocument::ErrorIDToName(error));
            doc.Parse(validString.c_str());
        }

        auto root = parser->root;
        root->root = root;
        root->is_valid = true;

        auto handle = tinyxml2::XMLConstHandle(doc).FirstChildElement();
        auto element = handle.ToElement();
        while(element) {
            auto tag = BSMLDocParser::get_parser(element->Name())->parse(*element);
            root->AddChild(tag);

            handle = handle.NextSiblingElement();
            element = handle.ToElement();
        }

        return parser;
    }

    std::shared_ptr<BSMLParser> BSMLParser::parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host) {
        auto parser = parse(str);
        parser->Construct(parent, host);
        return parser;
    }

    void BSMLParser::Construct(UnityEngine::Transform* parent, Il2CppObject* host) {
        parserParams->host = host;
        std::vector<ComponentTypeWithData*> components;

        INFO("Making values from host fields, props and methods");
        auto values = BSMLValue::MakeValues(host);
        for (auto& [key, value] : values) {
            INFO("Got value: {}", key);
            parserParams->AddValue(key, value);
        }

        auto actions = BSMLAction::MakeActions(host);
        for (auto& [key, action] : actions) {
            INFO("Got action: {}", key);
            parserParams->AddAction(key, action);
        }
        
        /// when making from a new "root" we skip the root itself
        root->HandleChildren(parent, *parserParams, components);

        for (auto comp : components) {
            comp->typeHandler->HandleTypeAfterParse(*comp, *parserParams);
        }

        for (auto component : components) {
            delete component;
        }

        components.clear();
    }

    std::shared_ptr<BSMLParserParams> BSMLParser::Construct(const BSMLNode* root, UnityEngine::Transform* parent, Il2CppObject* host) {
        auto parserParams = std::make_shared<BSMLParserParams>();
        parserParams->host = host;
        std::vector<ComponentTypeWithData*> components;

        INFO("Making values from host fields, props and methods");
        auto values = BSMLValue::MakeValues(host);
        for (auto& [key, value] : values) {
            INFO("Got value: {}", key);
            parserParams->AddValue(key, value);
        }

        root->HandleChildren(parent, *parserParams, components);
        for (auto comp : components) {
            comp->typeHandler->HandleTypeAfterParse(*comp, *parserParams);
        }

        for (auto component : components) {
            delete component;
        }

        components.clear();
        return parserParams;
    }

}