#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/Settings/ToggleSettingData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class ToggleSettingTag : private BSMLTag {
        public:
            ToggleSettingTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class ToggleSettingTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            ToggleSettingData toggleSettingData;
            LayoutElementData layoutElementData;
            RectTransformData rectTransformData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}