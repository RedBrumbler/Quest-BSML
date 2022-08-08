#include "BSML/Tags/Settings/SubmenuTag.hpp"
#include "BSML.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

namespace BSML {
    static BSMLNodeParser<SubmenuTag> submenuTagParser({"settings-submenu"});
    UnityEngine::GameObject* SubmenuTag::CreateObject(UnityEngine::Transform* parent) const {
        auto go = UnityEngine::GameObject::New_ctor("BSMLSubMenu");
        go->get_transform()->SetParent(parent, false);
        return go;
    }
}