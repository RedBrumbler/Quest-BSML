#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/TextPageScrollView.hpp"

DECLARE_CLASS_CORDL(BSML, TextPageScrollViewRefresher, UnityEngine::MonoBehaviour,
    DECLARE_FIELDS(
        DECLARE_INSTANCE_FIELD(HMUI::TextPageScrollView, scrollView);
    );

    FIELD_ACCESSOR(scrollView);

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, OnRectTransformDimensionsChange);
)
