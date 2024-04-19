#include "hooking.hpp"
#include "logging.hpp"
#include "GlobalNamespace/LevelListTableCell.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "TMPro/TMP_Text.hpp"

MAKE_AUTO_HOOK_MATCH(LevelListTableCell_RefreshVisuals, &GlobalNamespace::LevelListTableCell::RefreshVisuals, void, GlobalNamespace::LevelListTableCell* self) {
    LevelListTableCell_RefreshVisuals(self);
    auto rt = self->_songNameText->rectTransform;
    auto offsetMax = rt->offsetMax;
    offsetMax.y = rt->offsetMin.y + 6.5f; // default is 5.74
    rt->offsetMax = offsetMax;
}
