#include "BSML/Data/ButtonIconImageData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

namespace BSML {
    ButtonIconImageData::ButtonIconImageData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("icon", icon);
    }
    
    void ButtonIconImageData::Apply(BSML::ButtonIconImage* buttonIconImage) const {
        if (!buttonIconImage) {
            ERROR("nullptr passed to ButtonIconImageData::Apply");
            return;
        }
        if (!get_icon().empty()) buttonIconImage->SetIcon(get_icon());
    }
}