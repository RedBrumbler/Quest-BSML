#include "hooking.hpp"

#include "HMUI/SegmentedControl.hpp"
#include "HMUI/SegmentedControlCell.hpp"
#include "System/Action_2.hpp"
#include "System/Action_1.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"


MAKE_AUTO_HOOK_ORIG_MATCH(SegmentedControl_HandleCellSelectionDidChange, &HMUI::SegmentedControl::HandleCellSelectionDidChange, void, HMUI::SegmentedControl* ptr, HMUI::SelectableCell selectableCell, HMUI::SelectableCell::TransitionType transitionType, bs_hook::Il2CppWrapperType changeOwner) {
    HMUI::SegmentedControl self{ptr};

    if (self.selectedCellNumber == -1) {
        HMUI::SegmentedControlCell segmentedCell {selectableCell.convert()};
        self.selectedCellNumber = segmentedCell.cellNumber;
        if (self.didSelectCellEvent) {
            self.didSelectCellEvent.Invoke(self, segmentedCell.cellNumber);
        }

        System::Action_1<int> value{nullptr};
        if (self.callbacks.TryGetValue(segmentedCell.cellNumber, byref(value))) {
            if (value) value.Invoke(segmentedCell.cellNumber);
        }

    } else {
        SegmentedControl_HandleCellSelectionDidChange(ptr, selectableCell, transitionType, changeOwner);
    }
}
