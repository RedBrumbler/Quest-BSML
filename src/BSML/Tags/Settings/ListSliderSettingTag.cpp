#include "BSML/Tags/Settings/ListSliderSettingTag.hpp"
#include "logging.hpp"

#include "BSML/Components/Settings/ListSliderSetting.hpp"

#include "UnityEngine/GameObject.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ListSliderSettingTag> listSliderSettingTagParser({"list-slider-setting"});
}