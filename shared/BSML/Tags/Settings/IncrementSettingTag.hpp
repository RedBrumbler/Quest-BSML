#pragma once

#include "../Settings/IncDecSettingTag.hpp"
#include "../../Components/Settings/IncrementSetting.hpp"

namespace BSML {
    class IncrementSettingTag : public IncDecSettingTag<BSML::IncrementSetting> {
    private:
        using Base = IncDecSettingTag<BSML::IncrementSetting>;
    public:
        IncrementSettingTag() : Base() {}
    private:
        virtual UnityEngine::GameObject CreateObject(UnityEngine::Transform parent) const override;
            return Base::CreateObject(parent);
        }
    };
}
