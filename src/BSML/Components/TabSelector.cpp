#include "BSML/Components/TabSelector.hpp"
#include "logging.hpp"

#include "Helpers/delegates.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"

DEFINE_TYPE(BSML, TabSelector);

namespace BSML {
    void TabSelector::ctor() {
        tabs = List<Tab>::New_ctor();
        visibleTabs = List<Tab>::New_ctor();
        pageCount = -1;
    }

    int TabSelector::get_page() {
        if (currentPage < 0) {
            return currentPage = 0;
        }
        int maxPages = (visibleTabs.Count - 1) / pageCount;
        if (currentPage > maxPages) {
            return currentPage = maxPages;
        }
        return currentPage;
    }

    int TabSelector::get_pageCount() {
        return _pageCount;
    }

    void TabSelector::set_pageCount(int value) {
        _pageCount = value;
        if (tabs.Count > 0) Refresh();
    }

    void TabSelector::Setup(const BSMLParserParams& parserParams) {
        DEBUG("TabSelector setup is ran!");
        if (Il2CppString::IsNullOrEmpty(tabTag)) {
            ERROR("Tab selector must have tab-tag!");
            return;
        }

        tabs.Clear();

        for (auto go : parserParams.GetObjectsWithTag(tabTag)) {
            auto tab = go.GetComponent<Tab>();
            tabs.Add(tab);
            tab.selector = this;
        }

        DEBUG("Got {} tabs!", tabs.Count);

        if (!System::String::IsNullOrEmpty(leftButtonTag)) {
            auto& leftButtons = parserParams.GetObjectsWithTag(leftButtonTag);
            if (!leftButtons.empty()) leftButton = leftButtons[0].GetComponent<UnityEngine::UI::Button>();
        }
        if (leftButton) {
            auto delegate = MakeUnityAction([self = *this](){ self.PageLeft(); });
            leftButton.onClick.AddListener(delegate);
        }
        if (!System::String::IsNullOrEmpty(rightButtonTag))  {
            auto& rightButtons = parserParams.GetObjectsWithTag(rightButtonTag);
            if (!rightButtons.empty()) rightButton = rightButtons[0].GetComponent<UnityEngine::UI::Button>();
        }
        if (rightButton) {
            auto delegate = MakeUnityAction([self = *this](){ self.PageRight(); });
            rightButton.onClick.AddListener(delegate);
        }

        DEBUG("left button: {}, right button: {}", leftButton != nullptr, rightButton != nullptr);
        Refresh();

        auto tabSelectedInfo = il2cpp_functions::class_get_method_from_name(il2cpp_functions::object_get_class(convert()), "TabSelected", 2);
        auto delegate = MakeSystemAction<HMUI::SegmentedControl, int>(convert(), tabSelectedInfo);
        textSegmentedControl.add_didSelectCellEvent(delegate);
        textSegmentedControl.SelectCellWithNumber(0);
        TabSelected(textSegmentedControl, 0);
    }

    void TabSelector::TabSelected(HMUI::SegmentedControl segmentedControl, int index) {
        lastClickedPage = currentPage;
        lastClickedIndex = index;
        if (get_pageCount() != -1) index += pageCount * currentPage;
        int visibleCount = 0;
        Tab theTab {nullptr};
        for (auto tab : tabs) {
            tab.gameObject.SetActive(false);
            if (tab.isVisible) {
                if (index == visibleCount) theTab = tab;
                visibleCount++;
            }
        }

        // if our index is above or equal to the visible cells, return
        if (index >= visibleCount) return;
        if (theTab) theTab.gameObject.SetActive(true);
    }

    void TabSelector::Refresh() {
        if (!isActiveAndEnabled) {
            shouldRefresh = true;
            return;
        }

        DEBUG("TabSelector Refresh is ran!");

        shouldRefresh = false;
        visibleTabs.Clear();
        for (auto tab : tabs) if (tab.isVisible) visibleTabs.Add(tab);

        if (pageCount == -1) {
            SetSegmentedControlTexts(visibleTabs);
        } else {
            currentPage = get_page();
            ListWrapper<Tab> usableTabs = List<Tab>::New_ctor();
            usableTabs.EnsureCapacity(pageCount);

            int start = pageCount * currentPage;
            int end = std::min(start + pageCount, visibleTabs.Count);
            for (int i = start; i < end; i++) {
                usableTabs.Add(visibleTabs[i]);
            }

            SetSegmentedControlTexts(usableTabs);

            if (leftButton) leftButton.interactable = currentPage > 0;
            if (rightButton) rightButton.interactable = currentPage < ((visibleTabs.Count - 1) / pageCount);

            TabSelected(nullptr, 0);
        }
    }

    void TabSelector::SetSegmentedControlTexts(ListWrapper<Tab> tabs) {
        // we have to use a list because Array does not implement IReadOnlyList
        auto texts = List<StringW>::New_ctor();
        texts.EnsureCapacity(tabs.Count);

        for (auto tab : tabs) {
            auto val = tab.tabKey;
            if (System::String::IsNullOrEmpty(val)) {
                val = tab.tabName;
            }
            texts.Add(val);

            DEBUG("tab Text added: {}", val);
        }

        textSegmentedControl.SetTexts(texts);
    }

    void TabSelector::PageLeft() {
        currentPage--;
        Refresh();
    }

    void TabSelector::PageRight() {
        currentPage++;
        Refresh();
    }

    void TabSelector::OnEnable() {
        if (shouldRefresh) Refresh();
    }
}
