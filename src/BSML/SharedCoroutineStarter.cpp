#include "BSML/SharedCoroutineStarter.hpp"

#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(BSML, SharedCoroutineStarter);

namespace BSML {
    SafePtrUnity<UnityEngine::MonoBehaviour> SharedCoroutineStarter::instance;

    UnityEngine::MonoBehaviour* SharedCoroutineStarter::get_instance() {
        if (!instance) {
            auto go = UnityEngine::GameObject::New_ctor("BSMLSharedCoroutineStarter");
            instance = go->AddComponent<SharedCoroutineStarter*>();
        }
        return instance.ptr();
    }
}
