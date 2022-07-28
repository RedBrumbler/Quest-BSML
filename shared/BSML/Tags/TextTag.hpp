#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class TextTagParser;
    class TextTag : public BSMLTag {
        public:
            TextTag() : BSMLTag() {}
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;
            
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;

            RectTransformData rectTransformData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}