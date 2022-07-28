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

    struct TypeHandlerArgument : std::string {
        operator bool();
        operator int();
        operator float();
        operator double();
        operator UnityEngine::Color();
        operator UnityEngine::Color32();
        
        std::optional<bool> tryParseBool();
        std::optional<int> tryParseInt();
        std::optional<float> tryParseFloat();
        std::optional<double> tryParseDouble();
        std::optional<UnityEngine::Color> tryParseColor();
        std::optional<UnityEngine::Color32> tryParseColor32();
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
                if (il2cpp_utils::IsConvertibleFrom(&classof(T)->byval_arg, &componentType.component->klass->byval_arg)) {
                    auto& cachedSetters = get_cachedSetters();
                    auto& cachedProps = get_cachedProps();
                    // for each key value pair
                    for (const auto &[key, value] : componentType.data) {
                        INFO("data pair: {}, {}", key, value);
                        // try to find the setter
                        auto itr = cachedSetters.find(key);
                        if (itr != cachedSetters.end()) {
                            INFO("got a setter!");
                            // execute the setter!
                            const std::string& val = value;
                            itr->second(reinterpret_cast<T>(componentType.component), *reinterpret_cast<const TypeHandlerArgument*>(&val));
                        }
                    }
                }
            }
        private:
            System::Type* cachedType = nullptr;
            SetterMap cachedSetters;
    };
}