#include "BSML/Data/SelectableData.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"

namespace BSML {
    SelectableData::SelectableData(const tinyxml2::XMLElement& elem) {
        GET_BSML_BOOL("interactable", interactable);
    }
    
    void SelectableData::Apply(UnityEngine::UI::Selectable* interactable) const {
        if (!interactable) {
            ERROR("nullptr passed to SelectableData::Apply");
            return;
        }
        interactable->set_interactable(this->get_interactable());
    }
}