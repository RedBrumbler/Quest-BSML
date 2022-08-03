#include "BSML/Tags/LoadingIndicatorTag.hpp"

#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "HMUI/ImageView.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<LoadingIndicatorTag> loadingIndicatorTagParser({"loading", "loading-indicator"});
    UnityEngine::GameObject* loadingTemplate = nullptr;
    UnityEngine::GameObject* LoadingIndicatorTag::CreateObject(UnityEngine::Transform* parent) const {
        if (!loadingTemplate || !Object::IsNativeObjectAlive(loadingTemplate)) {
            loadingTemplate = Resources::FindObjectsOfTypeAll<HMUI::ImageView*>().FirstOrDefault([](auto x){ return x->get_gameObject()->get_name() == "LoadingIndicator"; })->get_gameObject();
        }

        auto gameObject = Object::Instantiate(loadingTemplate, parent, false);
        gameObject->set_name("BSMLLoadingIndicator");

        gameObject->AddComponent<UI::LayoutElement*>();
        return gameObject;
    }
}

