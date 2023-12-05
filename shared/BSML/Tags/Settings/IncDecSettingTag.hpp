#pragma once

#include "../BSMLTag.hpp"
#include "../../Components/Settings/IncDecSetting.hpp"

namespace BSML {
    class IncDecSettingTagBase : public BSMLTag {
        public:
            IncDecSettingTagBase() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
            virtual System::Type get_type() const = 0;
    };

    template<typename T>
    requires(std::is_base_of_v<::BSML::IncDecSetting, T>)
    class IncDecSettingTag : public IncDecSettingTagBase {
        public:
            IncDecSettingTag() : IncDecSettingTagBase() {}
        protected:
            virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
                return IncDecSettingTagBase::CreateObject(parent);
            }
            System::Type get_type() const override { return System::Type(csTypeOf(T)); };
    };
}
