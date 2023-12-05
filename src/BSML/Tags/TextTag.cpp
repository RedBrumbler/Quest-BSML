#include "BSML/Tags/TextTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"
#include "logging.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/GameObject.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<TextTag> textTagParser({"text", "label"});
    UnityEngine::GameObject TextTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Text");
        auto gameObject = GameObject::New_ctor("BSMLText");
        gameObject.transform.SetParent(parent, false);

        // on PC this is a FormattableText, but we're skipping that for now at least
        auto textMesh = gameObject.AddComponent<HMUI::CurvedTextMeshPro>();
        textMesh.font = Helpers::GetMainTextFont();
        textMesh.fontSharedMaterial = Helpers::GetMainUIFontMaterial();
        textMesh.fontSize = 4;
        textMesh.color = {1.0f, 1.0f, 1.0f, 1.0f};
        textMesh.text = "BSMLText";

        auto rectTransform = textMesh.rectTransform;
        rectTransform.anchorMin = {0.5f, 0.5f};
        rectTransform.anchorMax = {0.5f, 0.5f};

        return gameObject;
    }
}
