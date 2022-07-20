#include "BSML/Tags/BSMLTag.hpp"
#include "BSMLMacros.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "System/Object.hpp"

namespace BSML {
    extern BSMLTag* invalid;

    BSMLTag::BSMLTag() : is_valid(false), children({}) {}

    BSMLTag::~BSMLTag() {
        INFO("Destruct BSMLTag {}", fmt::ptr(this));
        for (auto child : children) {
            // we can't delete the child if it's the invalid tag
            if (child != invalid)
                delete child;
        }
        children.clear();
    } 

    bool BSMLTag::valid() const { 
        return is_valid; 
    }

    void BSMLTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        // BSMLTag construct is just a passthrough to child
        CreateChildren(parent, host);
    }

    UnityEngine::GameObject* BSMLTag::CreateObject(UnityEngine::Transform* parent) const {
        static ConstString bsmlTag{"BSMLTag"};
        auto go = UnityEngine::GameObject::New_ctor(bsmlTag);
        go->get_transform()->SetParent(parent, false);
        return go;
    }

    void BSMLTag::CreateChildren(UnityEngine::Transform* parent, Il2CppObject* host) const {
        for (auto child : children) {
            child->Construct(parent, host);
        }
    }

    void BSMLTag::SetHostField(Il2CppObject* host, Il2CppObject* value) const {
        if (!host || id.empty()) return;

        // get the field info with il2cpp reflection
        auto fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, id.c_str());

        if (fieldInfo) {
            // if found, use it to check the type
            auto fieldKlass = il2cpp_utils::GetFieldClass(fieldInfo);

            // if field klass is the same as value klass, assign
            if (fieldKlass == value->klass)
                il2cpp_functions::field_set_value(host, fieldInfo, value);
        }
    }
    
    void BSMLTag::AddChild(BSMLTag* child) {
        children.emplace_back(child);
    }

    void BSMLTag::parse(const tinyxml2::XMLElement& elem) {
        is_valid = true;
        GET_BSML_STRING("id", id);
    }
}