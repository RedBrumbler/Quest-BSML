#include "BSML/Tags/Settings/SubmenuTag.hpp"
#include "BSML.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

namespace BSML {
    static BSMLTagParser<SubmenuTag> submenuTagParser({"settings-submenu"});
    void SubmenuTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        BSML::parse_and_construct("<text text='tag \"settings-submenu\" is not supported on quest'/>", go->get_transform(), host);
    }

    UnityEngine::GameObject* SubmenuTag::CreateObject(UnityEngine::Transform* parent) const {
        auto go = UnityEngine::GameObject::New_ctor("BSMLSubmenu");
        go->get_transform()->SetParent(parent, false);
        return go;
    }

    void SubmenuTag::parse(const tinyxml2::XMLElement& elem) {
    }
}