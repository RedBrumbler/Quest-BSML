#include "BSML/TypeHandlers/TypeHandler.hpp"
#include "Helpers/utilities.hpp"

namespace BSML {
    
    std::vector<TypeHandlerBase*>& TypeHandlerBase::get_typeHandlers() {
        static std::vector<TypeHandlerBase*> typeHandlers = {};
        return typeHandlers;
    }

    const TypeHandlerBase::PropMap& TypeHandlerBase::get_cachedProps() {
        if (cachedProps.empty())
            cachedProps = get_props();
        return cachedProps;
    }

    void TypeHandlerBase::RegisterTypeHandler(TypeHandlerBase* typeHandler) {
        auto itr = std::find(get_typeHandlers().begin(), get_typeHandlers().end(), typeHandler);
        if (itr == get_typeHandlers().end()) {
            INFO("Registered type handler");
            get_typeHandlers().emplace_back(typeHandler);
        }
        INFO("type handler count: {}", get_typeHandlers().size());
    }

    void TypeHandlerBase::UnRegisterTypeHandler(TypeHandlerBase* typeHandler) {
        auto itr = std::find(get_typeHandlers().begin(), get_typeHandlers().end(), typeHandler);
        if (itr != get_typeHandlers().end()) {
            INFO("UnRegistered type handler");
            get_typeHandlers().erase(itr, itr++);
        }
        INFO("type handler count: {}", get_typeHandlers().size());
    }
    
    /// makes a string that's lowercase
    std::string toLower(std::string_view str) {
        std::string ret{str.data(), str.size()};
        std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
        return ret;
    }
    /// parsess a bool from a string
    std::optional<bool> TypeHandlerArgument::tryParseBool() const {
        auto lower = toLower(*this);
        if (lower == "true")
            return true;
        if (lower == "false")
            return false;
        return std::nullopt;
    }
    
    std::optional<int> TypeHandlerArgument::tryParseInt() const {
        const char* begin = data();
        char* end = nullptr;
        int result = strtol(begin, &end, 10);
        if (*begin == '\0') return std::nullopt;
        if (end == begin || *end != '\0') return std::nullopt;
        return result;
    }

    std::optional<float> TypeHandlerArgument::tryParseFloat() const {
        auto d = tryParseDouble();
        return d.has_value() ? std::make_optional<float>(d.value()) : std::nullopt;
    }
    
    std::optional<double> TypeHandlerArgument::tryParseDouble() const {
        const char* begin = data();
        char* end = nullptr;
        double result = strtod(begin, &end);
        if (*begin == '\0') return std::nullopt;
        if (end == begin || *end != '\0') return std::nullopt;
        return result;
    }

    std::optional<UnityEngine::Color> TypeHandlerArgument::tryParseColor() const {
        return Utilities::ParseHTMLColorOpt(*this);
    }

    std::optional<UnityEngine::Color32> TypeHandlerArgument::tryParseColor32() const {
        return Utilities::ParseHTMLColor32Opt(*this);
    }

    const MethodInfo* TypeHandlerArgument::asMethodInfo(Il2CppObject* host, int argCount) const {
        return il2cpp_functions::class_get_method_from_name(host->klass, data(), argCount);
    }

    const MethodInfo* TypeHandlerArgument::asSetter(Il2CppObject* host) const {
        auto name = "set_" + this->operator std::string();
        return il2cpp_functions::class_get_method_from_name(host->klass, name.c_str(), 1);
    }

    const MethodInfo* TypeHandlerArgument::asGetter(Il2CppObject* host) const {
        auto name = "get_" + this->operator std::string();
        return il2cpp_functions::class_get_method_from_name(host->klass, name.c_str(), 1);
    }

    FieldInfo* TypeHandlerArgument::asFieldInfo(Il2CppObject* host) const {
        return il2cpp_functions::class_get_field_from_name(host->klass, data());
    }

    TypeHandlerArgument::operator StringW() const {
        return StringW(*this);
    }

    TypeHandlerArgument::operator std::string() const {
        return {data(), size()};
    }
    
    TypeHandlerArgument::operator bool() const {
        auto result = tryParseBool();
        if (!result.has_value()) {
            ERROR("Could not parse bool from input '{}'", *this);
            return false;
        }
        return result.value();
    }
    
    TypeHandlerArgument::operator int() const {
        auto result = tryParseInt();
        if (!result.has_value()) {
            ERROR("Could not parse int from input '{}'", *this);
            return 0;
        }
        return result.value();
    }

    TypeHandlerArgument::operator float() const {
        auto result = tryParseFloat();
        if (!result.has_value()) {
            ERROR("Could not parse float from input '{}'", *this);
            return 0;
        }
        return result.value();
    }

    TypeHandlerArgument::operator double() const {
        auto result = tryParseDouble();
        if (!result.has_value()) {
            ERROR("Could not parse double from input '{}'", *this);
            return 0;
        }
        return result.value();
    }

    TypeHandlerArgument::operator UnityEngine::Color() const {
        auto result = tryParseColor();
        if (!result.has_value()) {
            ERROR("Could not parse color from input '{}'", *this);
            return {1.0, 1.0, 1.0, 1.0};
        }
        return result.value();
    }

    TypeHandlerArgument::operator UnityEngine::Color32() const {
        auto result = tryParseColor32();
        if (!result.has_value()) {
            ERROR("Could not parse color from input '{}'", *this);
            return {255, 255, 255, 255};
        }
        return result.value();
    }
}