#include "BSML/Components/ScrollIndicator.hpp"

DEFINE_TYPE(BSML, ScrollIndicator);

namespace BSML
{
    UnityEngine::RectTransform *ScrollIndicator::get_Handle()
    {
        return handle;
    }

    void ScrollIndicator::set_Handle(UnityEngine::RectTransform *value)
    {
        handle = value;
    }
}