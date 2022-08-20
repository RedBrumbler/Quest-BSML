#include "BSML.hpp"
#include "BSML/MenuButtons/MenuButtons.hpp"
#include "BSML/Settings/BSMLSettings.hpp"

extern "C" void load();

namespace BSML {
    void Init() {
        load();
    }

    std::shared_ptr<BSMLParser> parse(std::string_view str) {
        Init();
        return BSMLParser::parse(str);
    }
    
    std::shared_ptr<BSMLParser> parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host) {
        Init();
        return BSMLParser::parse_and_construct(str, parent, host);
    }

    namespace Register {
        MenuButton* RegisterMenuButton(std::string_view text, std::string_view hoverHint, std::function<void(void)> onClick) {
            auto btn = MenuButton::Make_new(text, hoverHint, onClick);
            if (RegisterMenuButton(btn)) return btn;
            btn->Finalize();
            return nullptr;
        }
    
        bool RegisterMenuButton(MenuButton* button) {
            return MenuButtons::get_instance()->Registerbutton(button);
        }
    
        bool UnRegisterMenuButton(MenuButton* button) {
            return MenuButtons::get_instance()->Registerbutton(button);
        }

        bool RegisterSettingsMenu(std::string_view name, std::string_view content_key, Il2CppObject* host, bool showExtraButtons) {
            return BSMLSettings::get_instance()->AddSettingsMenu(name, content_key, host, showExtraButtons);
        }

        bool UnRegisterSettingsMenu(Il2CppObject* host) {
            return BSMLSettings::get_instance()->RemoveSettingsMenu(host);
        }
    }
}