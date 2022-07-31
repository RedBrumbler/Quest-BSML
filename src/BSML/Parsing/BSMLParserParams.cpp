#include "BSML/Parsing/BSMLParserParams.hpp"

namespace BSML {
    // idk if returning a vector like this is valid
    const std::vector<UnityEngine::GameObject*>& BSMLParserParams::GetObjectsWithTag(const std::string& tag) const {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            static std::vector<UnityEngine::GameObject*> _;
            return _;
        } else {
            // especially this
            return itr->second;
        }
    }

    void BSMLParserParams::AddObjectWithTag(UnityEngine::GameObject* object, const std::string& tag) {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            objectsWithIds.insert({tag, {object}});
        } else {
            itr->second.emplace_back(object);
        }
    }

    void BSMLParserParams::AddObjectsWithTag(const std::vector<UnityEngine::GameObject*>& objects, const std::string& tag) {
        auto itr = objectsWithIds.find(tag);
        if (itr == objectsWithIds.end()) {
            objectsWithIds.emplace(tag, std::vector<UnityEngine::GameObject*>(objects.begin(), objects.end()));
        } else {
            itr->second.insert(itr->second.begin(), objects.begin(), objects.end());
        }
    }

    void BSMLParserParams::AddObjectWithTags(UnityEngine::GameObject* object, const std::vector<std::string>& tags) {
        for (auto tag : tags) {
            AddObjectWithTag(object, tag);
        }
    }
}