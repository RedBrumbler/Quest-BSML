#pragma once

#include "../BSMLTag.hpp"

#include "BSML/Components/Settings/SliderSettingBase.hpp"

namespace BSML {
    class GenericSliderSettingTagBase : public BSMLTag {
        public:
            GenericSliderSettingTagBase() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
            virtual System::Type* get_type() const = 0;
    };

    template<typename T>
    requires(std::is_convertible_v<T, ::BSML::SliderSettingBase*>)
    class GenericSliderSettingTag : public GenericSliderSettingTagBase {
        public:
            GenericSliderSettingTag() : GenericSliderSettingTagBase() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override {
                return GenericSliderSettingTagBase::CreateObject(parent);
            }
            System::Type* get_type() const override { return reinterpret_cast<System::Type*>(csTypeOf(T)); };
    };
}