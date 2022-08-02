#pragma once

#include "BSML/Tags/BSMLTag.hpp"

#include "BSML/Components/Settings/SliderSettingBase.hpp"

namespace BSML {
    class GenericSliderSettingTagBase : public BSMLTag {
        public:
            GenericSliderSettingTagBase() : BSMLTag() {}
        
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override;
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override;

            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            
            virtual System::Type* get_type() const = 0;
    };

    template<typename T>
    requires(std::is_convertible_v<T, ::BSML::SliderSettingBase*>)
    class GenericSliderSettingTag : public GenericSliderSettingTagBase {
        public:
            GenericSliderSettingTag() : GenericSliderSettingTagBase() {}
            virtual void Construct(UnityEngine::Transform* parent, Il2CppObject* host = nullptr) const override {
                GenericSliderSettingTagBase::Construct(parent, host);
            }
        protected:
            virtual void parse(const tinyxml2::XMLElement& elem) override {
                GenericSliderSettingTagBase::parse(elem);
            }
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return GenericSliderSettingTagBase::CreateObject(parent);
            }
            System::Type* get_type() const override { return reinterpret_cast<System::Type*>(csTypeOf(T)); };
    };
}