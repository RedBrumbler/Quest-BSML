#pragma once

#include <string>
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"


/// @brief a thin wrapper around a string view, to make parsing strings for values much more convenient
struct StringParseHelper : std::string_view {
    /// pass the normal constructors through to the base, these are the only ones we need
    StringParseHelper(const char* str) : std::string_view(str) {}
    StringParseHelper(const char* str, size_type len) : std::string_view(str, len) {}
    StringParseHelper(const std::string& str) : std::string_view(str.c_str(), str.size()) {}

    /// @return StringW
    operator StringW() const;
    /// @return std::string
    operator std::string() const;
    /// @return bool or false if invalid bool string
    operator bool() const;
    /// @return int or 0 if invalid int string
    operator int() const;
    /// @return float or 0 if invalid float string
    operator float() const;
    /// @return double or 0 if invalid double string
    operator double() const;
    /// @return Color or white if invalid color string
    operator UnityEngine::Color() const;
    /// @return Color32 or white if invalid color string
    operator UnityEngine::Color32() const;

    /// @return optional containing bool value, or nullopt if invalid bool string 
    std::optional<bool> tryParseBool() const;
    /// @return optional containing int value, or nullopt if invalid int string 
    std::optional<int> tryParseInt() const;
    /// @return optional containing float value, or nullopt if invalid float string 
    std::optional<float> tryParseFloat() const;
    /// @return optional containing double value, or nullopt if invalid double string 
    std::optional<double> tryParseDouble() const;
    /// @return optional containing color value, or nullopt if invalid color string 
    std::optional<UnityEngine::Color> tryParseColor() const;
    /// @return optional containing color32 value, or nullopt if invalid color string 
    std::optional<UnityEngine::Color32> tryParseColor32() const;

    /// @param host the object in which' klass to look for a method
    /// @param argCount amount of args for the expected method
    /// @return method info for the method this string view would point to on host klass, nullptr if not found or wrong argCount
    const MethodInfo* asMethodInfo(Il2CppObject* host, int argCount = 0) const;

    /// @param host the object in which' klass to look for a method
    /// @return method info for the setter this string view would point to on host klass, nullptr if not found
    const MethodInfo* asSetter(Il2CppObject* host) const;

    /// @param host the object in which' klass to look for a method
    /// @return method info for the getter this string view would point to on host klass, nullptr if not found
    const MethodInfo* asGetter(Il2CppObject* host) const;

    /// @param host the object in which' klass to look for a field
    /// @return field info for the getter this string view would point to on host klass, nullptr if not found
    FieldInfo* asFieldInfo(Il2CppObject* host) const;
};