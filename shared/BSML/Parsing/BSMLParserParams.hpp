#pragma once

#include "UnityEngine/GameObject.hpp"
#include <map>
#include <vector>
#include <string>

namespace BSML {
    class BSMLTag;
    class BSMLParserParams {
        public:
            BSMLParserParams(Il2CppObject* host, const BSMLTag* root) : host(host), root(root) {}
            // const applpies to the ptr itself now, so the value can not change
            // the host object is not const though, so it can be changed
            Il2CppObject* const host;
            const BSMLTag* const root;

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
        private:
            std::map<std::string, std::vector<UnityEngine::GameObject*>> objectsWithIds;
    };
}