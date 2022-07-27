#include "BSML/Data/ScrollIndicatorData.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

namespace BSML {
    ScrollIndicatorData::ScrollIndicatorData(const tinyxml2::XMLElement& elem) {
        GET_BSML_BOOL("preserve-aspect", preserveAspect);
    }
    
    void ScrollIndicatorData::Apply(HMUI::VerticalScrollIndicator* indicator) const {
        if (!indicator) {
            ERROR("nullptr passed to ScrollIndicatorData::Apply");
            return;
        }
    }
}