#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/ClickableTextData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class ClickableTextTagParser;
    class ClickableTextTag : public BSMLTag {
        public:
            ClickableTextTag() : BSMLTag() {}
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class ClickableTextTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;
            
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;

            RectTransformData rectTransformData;
            ClickableTextData clickableTextData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}