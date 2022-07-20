#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutGroupData.hpp"
#include "BSML/Data/ContentSizeFitterData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/BackgroundableData.hpp"
#include "BSML/Data/HorizontalOrVerticalLayoutGroupData.hpp"

namespace BSML {
    class VerticalTagParser;
    class VerticalTag : private BSMLTag {
        public:
            VerticalTag() : BSMLTag() {}
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class VerticalTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;

            BackgroundableData backgroundableData;
            ContentSizeFitterData contentSizeFitterData;
            HorizontalOrVerticalLayoutGroupData horizontalOrVerticalLayoutGroupData;
            LayoutElementData layoutElementData;
            LayoutGroupData layoutGroupData;
            RectTransformData rectTransformData;
    };
}
