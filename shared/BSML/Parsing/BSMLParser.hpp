#pragma once

#include "../ComponentTypeWithData.hpp"
#include "BSMLParserParams.hpp"
#include "BSMLNode.hpp"

namespace BSML {
    class BSMLParser {
        public:
            BSMLParser();
            ~BSMLParser();

            static std::shared_ptr<BSMLParser> parse(std::string_view str);
            static std::shared_ptr<BSMLParser> parse_and_construct(std::string_view str, UnityEngine::Transform* parent, bs_hook::Il2CppWrapperType host);
            void Construct(UnityEngine::Transform parent, bs_hook::Il2CppWrapperType host);
            static std::shared_ptr<BSMLParserParams> Construct(const BSMLNode* root, UnityEngine::Transform* parent, bs_hook::Il2CppWrapperType host);

            std::shared_ptr<BSMLParserParams> parserParams;
            BSMLNode* root;
    };
}
