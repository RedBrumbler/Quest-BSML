#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/ButtonIconImageData.hpp"
#include "BSML/Data/SelectableData.hpp"
#include "BSML/Data/ButtonData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutGroupData.hpp"
#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSML/Data/LayoutElementData.hpp"

namespace BSML {
    class ButtonWithIconTag : public BSMLTag {
        public:
            ButtonWithIconTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            SelectableData selectableData;
            ButtonIconImageData buttonIconImageData;
            ButtonData buttonData; 
            ContentSizeFitterData contentSizeFitterData;
            LayoutElementData layoutElementData;
            LayoutGroupData layoutGroupData;
            RectTransformData rectTransformData;
    };
}