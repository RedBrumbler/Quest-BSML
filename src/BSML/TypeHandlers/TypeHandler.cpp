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
    std::optional<bool> TypeHandlerArgument::tryParseBool() {
        auto lower = toLower(*this);
        if (lower == "true")
            return true;
        if (lower == "false")
            return false;
        return std::nullopt;
    }
    
    std::optional<int> TypeHandlerArgument::tryParseInt() {
        const char* begin = c_str();
        char* end = nullptr;
        int result = strtol(begin, &end, 10);
        if (*begin == '\0') return std::nullopt;
        if (end == begin || *end != '\0') return std::nullopt;
        return result;
    }

    std::optional<float> TypeHandlerArgument::tryParseFloat() {
        auto d = tryParseDouble();
        return d.has_value() ? std::make_optional<float>(d.value()) : std::nullopt;
    }
    
    std::optional<double> TypeHandlerArgument::tryParseDouble() {
        const char* begin = c_str();
        char* end = nullptr;
        double result = strtod(begin, &end);
        if (*begin == '\0') return std::nullopt;
        if (end == begin || *end != '\0') return std::nullopt;
        return result;
    }

    std::optional<UnityEngine::Color> TypeHandlerArgument::tryParseColor() {
        return Utilities::ParseHTMLColorOpt(*this);
    }

    std::optional<UnityEngine::Color32> TypeHandlerArgument::tryParseColor32() {
        return Utilities::ParseHTMLColor32Opt(*this);
    }

    TypeHandlerArgument::operator bool() {
        return tryParseBool().value_or(false);
    }
    
    TypeHandlerArgument::operator int() {
        return tryParseInt().value_or(0);
    }

    TypeHandlerArgument::operator float() {
        return tryParseFloat().value_or(0);
    }

    TypeHandlerArgument::operator double() {
        return tryParseDouble().value_or(0);
    }

    TypeHandlerArgument::operator UnityEngine::Color() {
        return tryParseColor().value_or(UnityEngine::Color(1.0, 1.0, 1.0, 1.0));
    }

    TypeHandlerArgument::operator UnityEngine::Color32() {
        return tryParseColor32().value_or(UnityEngine::Color32(255, 255, 255, 255));
    }
}