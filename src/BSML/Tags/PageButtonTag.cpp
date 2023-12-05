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
    static BSMLNodeParser<PageButtonTag> pageButtonTagParser({"page-button", "pg-button"});

    Button get_pageButtonTemplate() {
        static SafePtrUnity<Button> pageButtonTemplate;
        if (!pageButtonTemplate) {
            pageButtonTemplate = Resources::FindObjectsOfTypeAll<Button>().LastOrDefault([&](auto x){ return x.name == "UpButton"; });
        }
        return Button(pageButtonTemplate.ptr());
    }

    UnityEngine::GameObject PageButtonTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Page button");
        auto pageButtonTemplate = get_pageButtonTemplate();
        auto button = Object::Instantiate(pageButtonTemplate, parent, false);
        auto gameObject = button.gameObject;
        gameObject.SetActive(false);
        gameObject.name = "BSMLPageButton";
        button.interactable = true;

        RectTransform transform {button.transform.convert()};
        auto pageButton = gameObject.AddComponent<PageButton>();

        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(button);
        externalComponents.Add(transform);
        externalComponents.Add(pageButton);

        auto btnIcon = gameObject.AddComponent<ButtonIconImage>();
        btnIcon.image = gameObject.GetComponentsInChildren<Image>(true).FirstOrDefault([&](auto x){ return x.name == "Icon"; });
        externalComponents.Add(btnIcon);

        auto buttonSizeFitter = gameObject.AddComponent<ContentSizeFitter>();
        buttonSizeFitter.verticalFit = ContentSizeFitter::FitMode::PreferredSize;
        buttonSizeFitter.horizontalFit = ContentSizeFitter::FitMode::PreferredSize;
        externalComponents.Add(buttonSizeFitter);

        auto layoutElement = gameObject.AddComponent<LayoutElement>();
        layoutElement.preferredWidth = -1;
        layoutElement.preferredHeight = -1;
        layoutElement.flexibleHeight = 0;
        layoutElement.flexibleWidth = 0;

        RectTransform buttonTransform {transform.GetChild(0).convert()};
        buttonTransform.anchorMin = {0, 0};
        buttonTransform.anchorMax = {1, 1};
        buttonTransform.sizeDelta = {0, 0};
        transform.pivot = { 0.5f, 0.5f };
        externalComponents.Add(layoutElement);

        gameObject.SetActive(true);
        return gameObject;
    }
}
