#include "BSML/Tags/BSMLTag.hpp"
#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "internal_macros.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

#include "System/Object.hpp"

UnityEngine::Component* GetExternalComponent(UnityEngine::GameObject* obj, BSML::ExternalComponents* externalComponents, System::Type* type) {
    UnityEngine::Component* result = nullptr;
    if (externalComponents) {
        result = externalComponents->GetByType(type);
    }
    return result ? result : obj->GetComponent(type);
}

namespace BSML {
    static BSMLTagParser<BSMLTag> bsmlTagParser({"bsml"});
    BSMLTag::BSMLTag() : is_valid(false), children({}) {}

    BSMLTag::~BSMLTag() {
        for (auto child : children) delete child;
        children.clear();
    } 

    bool BSMLTag::valid() const { 
        return is_valid; 
    }

    void BSMLTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        if (!valid()) {
            ERROR("Trying to construct an invalid tag, not doing that!");
            return;
        }

        BSMLParserParams parserParams;
        parserParams.host = host;
        parserParams.root = this;
        std::vector<ComponentTypeWithData*> componentInfo;

        Handle(parent, parserParams, componentInfo);
        // gotta clean up, or it's a memory leak
        for (auto info : componentInfo) {
            delete info;
        }
        componentInfo.clear();
    }

    void BSMLTag::Handle(UnityEngine::Transform* parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const {
        // create object
        auto currentObject = CreateObject(parent);
        auto externalComponents = currentObject->GetComponent<ExternalComponents*>();

        std::vector<ComponentTypeWithData*> localComponentInfo = {};
        auto& typeHandlers = TypeHandlerBase::get_typeHandlers();
        // get the type handlers for the components on currentObject
        for (auto typeHandler : typeHandlers) {
            auto type = typeHandler->get_type();
            auto component = GetExternalComponent(currentObject, externalComponents, type);
            if (component)
            {
                INFO("Found component {}", type->get_FullName());
                auto componentTypeWithData = new ComponentTypeWithData();
                componentTypeWithData->typeHandler = typeHandler;
                componentTypeWithData->component = component;
                componentTypeWithData->data = ComponentTypeWithData::GetParameters(attributes, typeHandler->get_cachedProps());
                localComponentInfo.emplace_back(componentTypeWithData);
            }
        }

        // handle type initially
        for (auto componentTypeWithData : localComponentInfo) {
            componentTypeWithData->typeHandler->HandleType(*componentTypeWithData, parserParams);
        }

        // set the host field if we can
        auto fieldInfo = il2cpp_functions::class_get_field_from_name(parserParams.host->klass, id.c_str());
        if (fieldInfo) {
            auto fieldSystemType = il2cpp_utils::GetSystemType(il2cpp_functions::field_get_type(fieldInfo));
            auto component = GetExternalComponent(currentObject, externalComponents, fieldSystemType);
            if (component) {
                SetHostField(parserParams.host, component);
            }
        }

        // handle children
        for (auto child : children) {
            child->Handle(currentObject->get_transform(), parserParams, componentInfo);
        }

        // handle type after children
        for (auto componentTypeWithData : localComponentInfo) {
            componentTypeWithData->typeHandler->HandleTypeAfterChildren(*componentTypeWithData, parserParams);
        }

        // add all localComponentInfo to global one
        componentInfo.insert(componentInfo.begin(), localComponentInfo.begin(), localComponentInfo.end());
    }

    UnityEngine::GameObject* BSMLTag::CreateObject(UnityEngine::Transform* parent) const {
        return parent->get_gameObject();
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
            // if value type is convertible to as field type, assign
            if (il2cpp_utils::IsConvertibleFrom(fieldInfo->type, &value->klass->byval_arg))
                il2cpp_functions::field_set_value(host, fieldInfo, value);
        }
    }
    
    void BSMLTag::AddChild(BSMLTag* child) {
        child->root = root;
        child->parent = this;
        children.emplace_back(child);
    }

    void BSMLTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing bsml tag");
        is_valid = true;
        GET_BSML_STRING("id", id);

        for (const tinyxml2::XMLAttribute* a = elem.FirstAttribute(); a; a = a->Next()) {
            attributes[a->Name()] = a->Value();
        }
    }
}