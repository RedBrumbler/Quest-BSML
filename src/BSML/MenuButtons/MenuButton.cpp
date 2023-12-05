#include "BSML/MenuButtons/MenuButton.hpp"
#include "logging.hpp"

DEFINE_TYPE(BSML, MenuButton)

namespace BSML {
    MenuButton* MenuButton::Make_new(std::string_view label, std::string_view hoverHint, std::function<void()> onClick) {
        auto self = MenuButton::New_ctor();
        self.interactable = true;
        self.text = label;

        self.hoverHint = hoverHint;

        if (onClick) {
            self.onClick = onClick;
        }

        return self;
    }

    bool MenuButton::get_interactable() {
        return internal.interactable;
    }

    void MenuButton::set_interactable(bool value) {
        internal.interactable = value;
        if (menuButton && menuButton.m_CachedPtr) {
            menuButton.interactable = value;
        }
    }

    void MenuButton::Click() {
        INFO("{} Click", text);
        if (onClick) {
            onClick();
        }
    }
}
