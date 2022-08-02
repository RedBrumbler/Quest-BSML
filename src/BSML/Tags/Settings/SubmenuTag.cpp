#include "BSML/Tags/Settings/SubmenuTag.hpp"
#include "BSML.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

namespace BSML {
    static BSMLTagParser<SubmenuTag> submenuTagParser({"settings-submenu"});
    UnityEngine::GameObject* SubmenuTag::CreateObject(UnityEngine::Transform* parent) const {
        auto go = UnityEngine::GameObject::New_ctor("BSMLSubmenu");
        go->get_transform()->SetParent(parent, false);
        return go;
    }
}