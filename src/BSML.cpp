#include "BSML.hpp"
#include "BSML/MenuButtons/MenuButtons.hpp"

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

    bool RegisterMenuButton(MenuButton* button) {
        return MenuButtons::get_instance()->Registerbutton(button);
    }

    bool UnRegisterMenuButton(MenuButton* button) {
        return MenuButtons::get_instance()->Registerbutton(button);
    }
}