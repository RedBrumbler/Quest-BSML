#include "BSML/Tags/PageButtonTag.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/ButtonIconImage.hpp"
#include "BSML/Components/PageButton.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/LayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "HMUI/HoverHint.hpp"
#include "HMUI/ImageView.hpp"
#include "GlobalNamespace/LocalizedHoverHint.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<PageButtonTag> pageButtonTagParser({"page-button", "pg-button"});
    Button* pageButtonTemplate = nullptr;

    void PageButtonTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto externalComponents = go->GetComponent<ExternalComponents*>();
        auto pageButton = externalComponents->Get<PageButton*>();
        auto button = externalComponents->Get<Button*>();

        SetHostField(host, pageButton);
        
        CreateChildren(go->get_transform(), host);

    }

    UnityEngine::GameObject* PageButtonTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Page button");
        if (!pageButtonTemplate || !Object::IsNativeObjectAlive(pageButtonTemplate)) {
            pageButtonTemplate = Resources::FindObjectsOfTypeAll<Button*>().LastOrDefault([&](auto x){ return x->get_name() == "UpButton"; });
        }

        auto button = Object::Instantiate(pageButtonTemplate, parent, false);
        auto gameObject = button->get_gameObject();
        gameObject->SetActive(false);
        gameObject->set_name("BSMLPageButton");
        button->set_interactable(true);

        auto transform = reinterpret_cast<RectTransform*>(button->get_transform());
        auto pageButton = gameObject->AddComponent<PageButton*>();
        
        auto externalComponents = gameObject->AddComponent<ExternalComponents*>();
        externalComponents->Add(button);
        externalComponents->Add(transform);
        externalComponents->Add(pageButton);

        auto btnIcon = gameObject->AddComponent<ButtonIconImage*>();
        btnIcon->image = gameObject->GetComponentsInChildren<Image*>(true).FirstOrDefault([&](auto x){ return x->get_name() == "Icon"; });
        externalComponents->Add(btnIcon);

        auto buttonSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        buttonSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        buttonSizeFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
        externalComponents->Add(buttonSizeFitter);

        auto layoutElement = gameObject->AddComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(-1);
        layoutElement->set_preferredHeight(-1);
        layoutElement->set_flexibleHeight(0);
        layoutElement->set_flexibleWidth(0);

        auto buttonTransform = reinterpret_cast<RectTransform*>(transform->GetChild(0));
        buttonTransform->set_anchorMin({0, 0});
        buttonTransform->set_anchorMax({1, 1});
        buttonTransform->set_sizeDelta({0, 0});
        transform->set_pivot({ 0.5f, 0.5f });
        externalComponents->Add(layoutElement);

        gameObject->SetActive(true);
        return gameObject;
    }

    void PageButtonTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing page button tag");
        this->::BSML::BSMLTag::parse(elem);
    }
}