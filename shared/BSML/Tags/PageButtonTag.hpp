#pragma once

#include "BSML/Tags/BSMLTag.hpp"
#include "BSML/Data/PageButtonData.hpp"
#include "BSML/Data/ButtonIconImageData.hpp"
#include "BSML/Data/SelectableData.hpp"
#include "BSML/Data/ButtonData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSML/Data/LayoutElementData.hpp"

namespace BSML {
    class PageButtonTag : public BSMLTag {
        public:
            PageButtonTag() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class PageButtonTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            SelectableData selectableData;
            ButtonData buttonData; 
            PageButtonData pageButtonData;
            ButtonIconImageData buttonIconImageData;
            ContentSizeFitterData contentSizeFitterData;
            LayoutElementData layoutElementData;
            RectTransformData rectTransformData;
    };
}