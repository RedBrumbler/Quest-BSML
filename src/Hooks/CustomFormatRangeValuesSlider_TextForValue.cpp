#include "hooking.hpp"
#include "HMUI/CustomFormatRangeValuesSlider.hpp"
#include "BSML/Components/Settings/SliderSetting.hpp"
#include <map>

MAKE_AUTO_HOOK_MATCH(CustomFormatRangeValuesSlider_TextForValue, &HMUI::CustomFormatRangeValuesSlider::TextForValue, StringW, HMUI::CustomFormatRangeValuesSlider* self, float value) {
    auto itr = BSML::SliderSetting::remappers.find(self);
    if (itr == BSML::SliderSetting::remappers.end()) return CustomFormatRangeValuesSlider_TextForValue(self, value);
    else return itr->second->TextForValue(value);
}