#include "BSML/Tags/ButtonTag.hpp"

#include "BSML/Components/ExternalComponents.hpp"
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

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ButtonTag> buttonTagParser({"button"});
    Button ButtonTag::get_buttonPrefab() const {
        static SafePtrUnity<Button> buttonPrefab;
        if (!buttonPrefab) {
            buttonPrefab = Resources::FindObjectsOfTypeAll<Button>().LastOrDefault([&](auto x){ return x.name == "PracticeButton"; });
        }
        return Button(buttonPrefab.ptr());
    }

    UnityEngine::GameObject ButtonTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Button");

        auto button = Object::Instantiate(get_buttonPrefab(), parent, false);
        button.name = "BSMLButton";
        button.interactable = true;

        RectTransform transform {button.transform.convert()};
        auto gameObject = button.gameObject;
        gameObject.SetActive(true);
        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(button);
        externalComponents.Add(transform);

        auto textObject = button.transform.Find("Content/Text").gameObject;
        Object::Destroy(textObject.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());

        auto textMesh = textObject.GetComponent<TMPro::TextMeshProUGUI>();
        textMesh.text = "BSMLButton";
        textMesh.richText = true;
        externalComponents.Add(textMesh);

        Object::Destroy(transform.Find("Content").GetComponent<LayoutElement>());

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

        return gameObject;
    }
}
