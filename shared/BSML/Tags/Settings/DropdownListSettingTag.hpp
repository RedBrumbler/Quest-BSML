#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/Settings/ListSettingData.hpp"
#include "BSML/Data/Settings/GenericSettingData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class DropdownListSettingTag : public BSMLTag {
        public:
            DropdownListSettingTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            GenericSettingData genericSettingData;
            ListSettingData listSettingData;
            LayoutElementData layoutElementData;
            RectTransformData rectTransformData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}