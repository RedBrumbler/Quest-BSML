#pragma once

#include "UnityEngine/GameObject.hpp"
#include "BSML/Parsing/BSMLValue.hpp"

#include <map>
#include <vector>
#include <string>

namespace BSML {
    class BSMLParserParams {
        friend class BSMLTag;
        friend class BSMLMacro;
        friend class BSMLDocParser;
        friend class BSMLParser;
        public:
            ~BSMLParserParams();
            /// @brief get the object vector for the given tag
            /// @param tag the tag to look for
            /// @return const reference to the vector
            const std::vector<UnityEngine::GameObject*>& GetObjectsWithTag(const std::string& tag) const;
            
            /// @brief add object with tag to the backing map;
            /// @param object the object to add
            /// @param tag the tag to add the object to
            void AddObjectWithTag(UnityEngine::GameObject* object, const std::string& tag);

            /// @brief add multiple objects with tag to the backing map;
            /// @param objects the objects to add
            /// @param tag the tag to add the objects to
            void AddObjectsWithTag(const std::vector<UnityEngine::GameObject*>& objects, const std::string& tag);
            
            /// @brief add an object to multiple tags in the backing map
            /// @param object the object to add
            /// @param tags the tags to add the object to
            void AddObjectWithTags(UnityEngine::GameObject* object, const std::vector<std::string>& tags);

            /// @brief pass the tagged objects from this into the other params;
            /// @param other the parser params to pass the objects into
            void PassTaggedObjects(BSMLParserParams& other) const;

            /// @brief Equivalent to getting a BSMLValue from PC
            /// @param key the key the value is saved to
            BSMLValue* TryGetValue(const std::string& key);

            /// @brief adds the BSMLValue to the map
            /// @param key the key the value is saved to
            /// @param value the value to save
            void AddValue(const std::string& key, BSMLValue* value);

            /// @brief get the host object
            Il2CppObject* get_host();
        private:
            std::map<std::string, std::vector<UnityEngine::GameObject*>> objectsWithIds;
            std::map<std::string, BSMLValue*> values;
            Il2CppObject* host;
    };
}