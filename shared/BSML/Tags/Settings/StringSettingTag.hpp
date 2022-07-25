#pragma once

#include "BSML/Tags/ModalKeyboardTag.hpp"

#include "BSML/Data/Settings/GenericSettingData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

namespace BSML {
    class StringSettingTag : public ModalKeyboardTag {
        private:
            using Base = ModalKeyboardTag;
        public:
            StringSettingTag() : Base() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            friend class StringSettingTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            GenericSettingData genericSettingData;
            LayoutElementData layoutElementData;
            TextMeshProUGUIData textMeshProUGUIData;
    };
}