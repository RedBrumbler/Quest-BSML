#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include <string>
#include <vector>
#include <map>

#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLNodeParser.hpp"
#include "BSML/ComponentTypeWithData.hpp"
#include "BSML/Parsing/BSMLParserParams.hpp"

namespace BSML {
    class BSMLNode {
        public:
            BSMLNode();
            virtual ~BSMLNode();

            virtual void Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const = 0;
            bool valid() const;
            void AddChild(BSMLNode* child);
            
        protected:
            friend class ::BSML::BSMLDocParser;
            friend class ::BSML::BSMLNodeParserBase;
            bool is_valid = false;
            BSMLNode* root;
            BSMLNode* parent;
            std::vector<BSMLNode*> children;
            std::map<std::string, std::string> attributes = {};

            virtual void parse(const tinyxml2::XMLElement& elem);
    };
}