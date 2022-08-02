#pragma once

#include <vector>
#include "tinyxml2/shared/tinyxml2.h"
#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLNodeParser.hpp"
#include "BSML/Parsing/BSMLNode.hpp"
#include "BSML/ComponentTypeWithData.hpp"
#include "BSML/Parsing/BSMLParserParams.hpp"

namespace BSML {
    class BSMLNodeParserBase;
    class BSMLDocParser;

    class BSMLTag : public BSMLNode {
        public:
            BSMLTag();

            void Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const override;
        protected:
            friend class ::BSML::BSMLDocParser;
            friend class ::BSML::BSMLNodeParserBase;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const;
            void SetHostField(Il2CppObject* host, Il2CppObject* value) const;
            std::string id;
            std::vector<std::string> tags;
    };
}