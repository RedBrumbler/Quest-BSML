#pragma once

#include "BSML/ComponentTypeWithData.hpp"
#include "BSMLParserParams.hpp"
#include "BSMLNode.hpp"

namespace BSML {
    class BSMLParser {
        public:
            BSMLParser();
            ~BSMLParser();

            static std::shared_ptr<BSMLParser> parse(std::string_view str);
            static std::shared_ptr<BSMLParser> parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host);
            void Construct(UnityEngine::Transform* parent, Il2CppObject* host);
            static std::shared_ptr<BSMLParserParams> Construct(const BSMLNode* root, UnityEngine::Transform* parent, Il2CppObject* host);

            BSMLParserParams parserParams;
            BSMLNode* root;
    };
}