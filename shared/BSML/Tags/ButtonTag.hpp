#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/SelectableData.hpp"
#include "BSML/Data/ButtonData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutGroupData.hpp"
#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class ButtonTag : private BSMLTag {
        public:
            ButtonTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class ButtonTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            virtual std::string get_PrefabButton() const;
            
            SelectableData selectableData;
            ButtonData buttonData; 
            ContentSizeFitterData contentSizeFitterData;
            LayoutElementData layoutElementData;
            LayoutGroupData layoutGroupData;
            RectTransformData rectTransformData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}