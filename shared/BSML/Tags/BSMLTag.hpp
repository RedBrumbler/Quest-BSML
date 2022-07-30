#pragma once

#include <vector>
#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLTagParser.hpp"
#include "BSML/ComponentTypeWithData.hpp"
#include "BSML/Parsing/BSMLParserParams.hpp"

namespace BSML {
    class BSMLTagParserBase;
    class BSMLDocParser;

    class BSMLTag {
        public:
            BSMLTag();
            ~BSMLTag();

            bool valid() const;

            void Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const;
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host) const;
            void AddChild(BSMLTag* child);
            
        protected:
            friend class ::BSML::BSMLDocParser;
            friend class ::BSML::BSMLTagParserBase;
            virtual void parse(const tinyxml2::XMLElement& elem);

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const;
            void SetHostField(Il2CppObject* host, Il2CppObject* value) const;
            void CreateChildren(UnityEngine::Transform* parent, Il2CppObject* host) const;
            
            BSMLTag* root;
            BSMLTag* parent;
            bool is_valid = false;
            std::string id;
            std::vector<BSMLTag*> children;
            std::vector<std::string> tags;
            std::map<std::string, std::string> attributes = {};
    };
}