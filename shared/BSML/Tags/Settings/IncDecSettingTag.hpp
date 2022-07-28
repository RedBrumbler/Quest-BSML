#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Data/Settings/GenericSettingData.hpp"
#include "BSML/Data/RectTransformData.hpp"
#include "BSML/Data/LayoutElementData.hpp"
#include "BSML/Data/TextMeshProUGUIData.hpp"

#include "BSML/Components/Settings/IncDecSetting.hpp"

namespace BSML {
    class IncDecSettingTagBase : public BSMLTag {
        public:
            IncDecSettingTagBase() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            virtual System::Type* get_type() const = 0;

            GenericSettingData genericSettingData;
            LayoutElementData layoutElementData;
            RectTransformData rectTransformData;
            TextMeshProUGUIData textMeshProUGUIData;
    };

    template<typename T>
    requires(std::is_convertible_v<T, ::BSML::IncDecSetting*>)
    class IncDecSettingTag : public IncDecSettingTagBase {
        public:
            IncDecSettingTag() : IncDecSettingTagBase() {}
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override {
                IncDecSettingTagBase::Construct(parent, host);
            }
        protected:
            friend class IncrementSettingTagParser;
            virtual void parse(const tinyxml2::XMLElement& elem) override {
                IncDecSettingTagBase::parse(elem);
            }
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return IncDecSettingTagBase::CreateObject(parent);
            }
            System::Type* get_type() const override { return reinterpret_cast<System::Type*>(csTypeOf(T)); };
    };
}