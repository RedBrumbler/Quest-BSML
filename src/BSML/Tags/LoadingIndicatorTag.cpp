#include "BSML/Tags/LoadingIndicatorTag.hpp"

#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<LoadingIndicatorTag> loadingIndicatorTagParser({"loading", "loading-indicator"});
    
    UnityEngine::GameObject* get_loadingTemplate() {
        static SafePtrUnity<UnityEngine::GameObject> loadingTemplate;
        if (!loadingTemplate) {
            loadingTemplate = Resources::FindObjectsOfTypeAll<HMUI::ImageView*>()->FirstOrDefault([](auto x){ return x->get_gameObject()->get_name() == "LoadingIndicator"; })->get_gameObject();
        }
        return loadingTemplate.ptr();
    }
    UnityEngine::GameObject* LoadingIndicatorTag::CreateObject(UnityEngine::Transform* parent) const {

        auto gameObject = Object::Instantiate(get_loadingTemplate(), parent, false);
        gameObject->set_name("BSMLLoadingIndicator");

        gameObject->AddComponent<UI::LayoutElement*>();
        return gameObject;
    }
}
