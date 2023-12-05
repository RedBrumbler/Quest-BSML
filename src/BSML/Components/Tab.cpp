#include "BSML/Components/Tab.hpp"
#include "BSML/Components/TabSelector.hpp"

DEFINE_TYPE(BSML, Tab);

namespace BSML {
    void Tab::ctor() {
        _isVisible = true;
    }

    bool Tab::get_isVisible() {
        return _isVisible;
    }

    void Tab::set_isVisible(bool value) {
        _isVisible = value;
        if (selector) selector.Refresh();
    }

    StringW Tab::get_tabName() {
        return _tabName ? _tabName : "";
    }

    void Tab::set_tabName(StringW value) {
        _tabName = value;
        if (selector) selector.Refresh();
    }

    StringW Tab::get_tabKey() {
        return _tabKey ? _tabKey : "";
    }

    void Tab::set_tabKey(StringW value) {
        _tabKey = value;
        if (selector) selector.Refresh();
    }

    TabSelector Tab::__get_selector() {
        static constexpr auto offset = Tab::___Base__Size + offsetof(___InternalRepresentation, selector);
        return custom_types::read_field<TabSelector>(convert(), offset);
    }
    void Tab::__set_selector(TabSelector selector) {
        static constexpr auto offset = Tab::___Base__Size + offsetof(___InternalRepresentation, selector);
        custom_types::write_field<TabSelector>(convert(), offset, std::forward(selector));
    }
}
