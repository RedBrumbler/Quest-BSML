#include "StringParseHelper.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

/// makes a string thats lowercase
std::string StringParseHelper::toLower() const {
    std::string ret{data(), size()};
    std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
    return ret;
}

std::string StringParseHelper::toUpper() const {
    std::string ret{data(), size()};
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}

std::optional<bool> StringParseHelper::tryParseBool() const {
    auto lower = toLower();
    if (lower == "true")
        return true;
    if (lower == "false")
        return false;
    return std::nullopt;
}

std::optional<int> StringParseHelper::tryParseInt() const {
    const char* begin = data();
    char* end = nullptr;
    int result = strtol(begin, &end, 10);
    if (*begin == '\0') return std::nullopt;
    if (end == begin || *end != '\0') return std::nullopt;
    return result;
}
std::optional<float> StringParseHelper::tryParseFloat() const {
    auto d = tryParseDouble();
    return d.has_value() ? std::make_optional<float>(d.value()) : std::nullopt;
}

std::optional<double> StringParseHelper::tryParseDouble() const {
    const char* begin = data();
    char* end = nullptr;
    double result = strtod(begin, &end);
    if (*begin == '\0') return std::nullopt;
    if (end == begin || *end != '\0') return std::nullopt;
    return result;
}
std::optional<UnityEngine::Color> StringParseHelper::tryParseColor() const {
    return BSML::Utilities::ParseHTMLColorOpt(*this);
}
std::optional<UnityEngine::Color32> StringParseHelper::tryParseColor32() const {
    return BSML::Utilities::ParseHTMLColor32Opt(*this);
}
const MethodInfo* minfo_from_name_in_parents(Il2CppClass* klass, const char* name, int argc) {
    if (!klass) return nullptr;
    auto minfo = il2cpp_functions::class_get_method_from_name(klass, name, argc);
    if (minfo) return minfo;
    return il2cpp_functions::class_get_method_from_name(klass->parent, name, argc);
}
const MethodInfo* StringParseHelper::asMethodInfo(Il2CppObject* host, int argCount) const {
    return minfo_from_name_in_parents(host->klass, data(), argCount);
}
const MethodInfo* StringParseHelper::asSetter(Il2CppObject* host) const {
    auto name = "set_" + this->operator std::string();
    return il2cpp_functions::class_get_method_from_name(host->klass, name.c_str(), 1);
}
const MethodInfo* StringParseHelper::asGetter(Il2CppObject* host) const {
    auto name = "get_" + this->operator std::string();
    return il2cpp_functions::class_get_method_from_name(host->klass, name.c_str(), 0);
}
FieldInfo* StringParseHelper::asFieldInfo(Il2CppObject* host) const {
    return il2cpp_functions::class_get_field_from_name(host->klass, data());
}
StringParseHelper::operator StringW() const {
    return StringW(*this);
}
StringParseHelper::operator std::string() const {
    return {data(), size()};
}

StringParseHelper::operator bool() const {
    auto result = tryParseBool();
    if (!result.has_value()) {
        ERROR("Could not parse bool from input '{}'", *this);
        return false;
    }
    return result.value();
}

StringParseHelper::operator int() const {
    auto result = tryParseInt();
    if (!result.has_value()) {
        ERROR("Could not parse int from input '{}'", *this);
        return 0;
    }
    return result.value();
}
StringParseHelper::operator float() const {
    auto result = tryParseFloat();
    if (!result.has_value()) {
        ERROR("Could not parse float from input '{}'", *this);
        return 0;
    }
    return result.value();
}
StringParseHelper::operator double() const {
    auto result = tryParseDouble();
    if (!result.has_value()) {
        ERROR("Could not parse double from input '{}'", *this);
        return 0;
    }
    return result.value();
}
StringParseHelper::operator UnityEngine::Color() const {
    auto result = tryParseColor();
    if (!result.has_value()) {
        ERROR("Could not parse color from input '{}'", *this);
        return {1.0, 1.0, 1.0, 1.0};
    }
    return result.value();
}
StringParseHelper::operator UnityEngine::Color32() const {
    auto result = tryParseColor32();
    if (!result.has_value()) {
        ERROR("Could not parse color from input '{}'", *this);
        return {255, 255, 255, 255};
    }
    return result.value();
}