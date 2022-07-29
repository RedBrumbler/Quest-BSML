#include "BSML/Tags/GridLayoutTag.hpp"
#include "BSML/Components/Backgroundable.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/GridLayoutGroup.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<GridLayoutTag> gridLayoutTagParser({"grid"});
    void GridLayoutTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto grid = go->GetComponent<UnityEngine::UI::GridLayoutGroup*>();
        SetHostField(host, grid);
        
        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* GridLayoutTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating GridLayout");
        auto gameObject = GameObject::New_ctor("BSMLGridLayoutGroup");
        gameObject->get_transform()->SetParent(parent, false);
        auto grid = gameObject->AddComponent<GridLayoutGroup*>();

        auto contentSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        contentSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        gameObject->AddComponent<Backgroundable*>();

        auto rectTransform = grid->get_rectTransform();
        rectTransform->set_anchorMin({0, 0});
        rectTransform->set_anchorMax({1, 1});
        rectTransform->set_sizeDelta({0, 0});

        gameObject->AddComponent<LayoutElement*>();
        return gameObject;
    }

    void GridLayoutTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing grid tag");
        this->::BSML::BSMLTag::parse(elem);
    }
}