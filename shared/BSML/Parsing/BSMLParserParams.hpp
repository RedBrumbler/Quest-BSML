#pragma once

namespace BSML {
    class BSMLTag;
    class BSMLParserParams {
        public:
            std::map<std::string, UnityEngine::Component*> objectsWithIds;
            Il2CppObject* host;
            const BSMLTag* root;

            void AddComponent(std::string id, UnityEngine::Component* component) {
                objectsWithIds[id] = component;
            }

            UnityEngine::Component* GetComponent(std::string id) {
                auto itr = objectsWithIds.find(id);
                if (itr != objectsWithIds.end())
                    return itr->second;
                return nullptr;
            }
    };
}