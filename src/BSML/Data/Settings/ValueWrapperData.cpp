#include "BSML/Data/Settings/ValueWrapperData.hpp"
#include "logging.hpp"
#include "BSMLMacros.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

namespace BSML {
    ValueWrapperData::ValueWrapperData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("field-name", fieldName);
        GET_BSML_STRING("field", fieldName);
        
        GET_BSML_STRING("on-change", onChange);
        GET_BSML_STRING("on-toggle", onChange);
        
        GET_BSML_STRING("property-name", propertyName);
        GET_BSML_STRING("property", propertyName);
    }

    void ValueWrapperData::Apply(BSML::ValueWrapper* wrapper, Il2CppObject* host) const {
        if (!wrapper || !host) {
            ERROR("nullptr passed to ValueWrapperData::Apply");
            return;
        }
        wrapper->host = host;
        
        SetterType type = SetterType::None;
        std::string setterName = "set_" + propertyName;
        std::string getterName = "get_" + propertyName;
        wrapper->setterInfo = il2cpp_functions::class_get_method_from_name(host->klass, setterName.c_str(), 1);
        wrapper->getterInfo = il2cpp_functions::class_get_method_from_name(host->klass, getterName.c_str(), 0);

        wrapper->fieldInfo = il2cpp_functions::class_get_field_from_name(host->klass, fieldName.c_str());
        wrapper->methodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onChange.c_str(), 0);
        
        if (wrapper->fieldInfo) type |= SetterType::Field;
        if (wrapper->setterInfo || wrapper->getterInfo) type |= SetterType::Property;
        if (wrapper->methodInfo) type |= SetterType::Method;

        wrapper->set_setterType(type);

        if (type == SetterType::None && !(propertyName.empty() && fieldName.empty() && onChange.empty())) {
            ERROR("No methods found for a value wrapper, are you sure the properties/methods/fields are correct?");
        }
    }
}