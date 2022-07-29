#pragma once

#include "BSML/ComponentTypeWithData.hpp"
#include "BSML/Parsing/BSMLParserParams.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"
#include "System/Type.hpp"
#include <string>
#include <vector>
#include <map>
#include <optional>
#include "logging.hpp"

namespace BSML {
    class TypeHandlerBase {
        public:
            TypeHandlerBase() { RegisterTypeHandler(this); }
            ~TypeHandlerBase() { UnRegisterTypeHandler(this); }
            using Aliases = std::vector<std::string>;
            using PropMap = std::map<std::string, Aliases>;
            const PropMap& get_cachedProps();

            virtual PropMap get_props() const = 0;
            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) = 0;
            virtual void HandleTypeAfterChildren(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) { }
            virtual void HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) { }

            virtual System::Type* get_type() = 0;
            static std::vector<TypeHandlerBase*>& get_typeHandlers();

        private:
            PropMap cachedProps;
            static void RegisterTypeHandler(TypeHandlerBase* typeHandler);
            static void UnRegisterTypeHandler(TypeHandlerBase* typeHandler);
    };

    struct TypeHandlerArgument : std::string_view {
        /// pass the normal constructors through to the base, these are the only ones we need
        TypeHandlerArgument(const char* str) : std::string_view(str) {}
        TypeHandlerArgument(const std::string& str) : std::string_view(str) {}

        // we go to StringW enough times that an operator cuts out a step
        operator StringW() const;
        // string view -> string doesn't normally exist
        operator std::string() const;
        operator bool() const;
        operator int() const;
        operator float() const;
        operator double() const;
        operator UnityEngine::Color() const;
        operator UnityEngine::Color32() const;
        
        std::optional<bool> tryParseBool() const;
        std::optional<int> tryParseInt() const;
        std::optional<float> tryParseFloat() const;
        std::optional<double> tryParseDouble() const;
        std::optional<UnityEngine::Color> tryParseColor() const;
        std::optional<UnityEngine::Color32> tryParseColor32() const;
    };

    template<typename T>
    requires(std::is_convertible_v<T, UnityEngine::Component*>)
    class TypeHandler : public TypeHandlerBase {
        public:
            TypeHandler() : TypeHandlerBase() {};

            using Setter = std::function<void(T, const TypeHandlerArgument&)>;
            using SetterMap = std::map<std::string, Setter>;
            using PropMap = TypeHandlerBase::PropMap;

            const SetterMap& get_cachedSetters() {
                if (cachedSetters.empty())
                    cachedSetters = get_setters();
                return cachedSetters;
            }

            virtual System::Type* get_type() override { 
                if (cachedType) return cachedType; 
                return (cachedType = reinterpret_cast<System::Type*>(csTypeOf(T))); 
            };

            virtual SetterMap get_setters() const = 0;

            virtual void HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) override {
                auto klass = classof(T);
                if (il2cpp_functions::class_is_assignable_from(klass, componentType.component->klass)) {
                    auto& cachedSetters = get_cachedSetters();
                    auto& cachedProps = get_cachedProps();
                    // for each key value pair
                    for (const auto &[key, value] : componentType.data) {
                        INFO("data pair: '{}', '{}'", key, value);
                        // try to find the setter
                        auto itr = cachedSetters.find(key);
                        if (itr != cachedSetters.end()) {
                            INFO("got a setter!");
                            // execute the setter!
                            itr->second(reinterpret_cast<T>(componentType.component), value);
                        }
                    }
                } else {
                    ERROR("klass {}::{} was not assignable from {}::{}", klass->namespaze, klass->name, componentType.component->klass->namespaze, componentType.component->klass->name);
                }
            }
        private:
            System::Type* cachedType = nullptr;
            SetterMap cachedSetters;
    };
}