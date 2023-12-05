#include "BSML/Tags/ButtonWithIconTag.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/ButtonIconImage.hpp"
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
    static BSMLNodeParser<ButtonWithIconTag> buttonWithIconTagParser({"button-with-icon", "icon-button"});

    Button get_buttonWithIconTemplate() {
        static SafePtrUnity<Button> buttonWithIconTemplate;
        if (!buttonWithIconTemplate) {
            buttonWithIconTemplate = Resources::FindObjectsOfTypeAll<Button>().LastOrDefault([&](auto x){ return x.name == "PracticeButton"; });
        }
        return Button(buttonWithIconTemplate.ptr());
    }

    UnityEngine::GameObject ButtonWithIconTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Button with icon");

        auto button = Object::Instantiate(get_buttonWithIconTemplate(), parent, false);
        button.name = "BSMLIconButton";
        button.interactable = true;
        RectTransform transform {button.transform.convert()};
        auto gameObject = button.gameObject;

        Object::Destroy(button.GetComponent<HMUI::HoverHint>());
        Object::Destroy(button.GetComponent<GlobalNamespace::LocalizedHoverHint>());

        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(button);
        externalComponents.Add(transform);

        auto contentTransform = transform.Find("Content");
        Object::Destroy(contentTransform.GetComponent<LayoutElement>());

        Object::Destroy(contentTransform.Find("Text").gameObject);

        auto iconImage = GameObject::New_ctor("Icon").AddComponent<HMUI::ImageView>();
        DEBUG("Iconimage: {}", fmt::ptr(iconImage));
        auto mat = Helpers::GetUINoGlowMat();
        DEBUG("Material: {}", fmt::ptr(mat));
        iconImage.material = mat;
        auto iconRectTransform = iconImage.rectTransform;
        iconRectTransform.SetParent(contentTransform, false);
        iconRectTransform.anchoredPosition = {0, 0};
        iconRectTransform.sizeDelta = {20, 20};
        iconRectTransform.anchorMin = {0.5f, 0.f};
        iconRectTransform.anchorMax = {0.5f, 0.5f};
        iconImage.preserveAspect = true;
        iconImage.sprite = Utilities::FindSpriteCached("EditIcon");

        auto btnIcon = button.gameObject.AddComponent<ButtonIconImage>();
        btnIcon.image = iconImage;
        externalComponents.Add(btnIcon);

        auto buttonSizeFitter = gameObject.AddComponent<ContentSizeFitter>();
        buttonSizeFitter.verticalFit = ContentSizeFitter::FitMode::PreferredSize;
        buttonSizeFitter.horizontalFit = ContentSizeFitter::FitMode::PreferredSize;
        externalComponents.Add(buttonSizeFitter);

        auto stackLayoutGroup = button.GetComponentInChildren<LayoutGroup>();
        if (stackLayoutGroup)
            externalComponents.Add(stackLayoutGroup);

        auto layoutElement = gameObject.AddComponent<LayoutElement>();
        layoutElement.preferredWidth = 30.0f;
        externalComponents.Add(layoutElement);

        gameObject.SetActive(true);
        return gameObject;
    }
}
