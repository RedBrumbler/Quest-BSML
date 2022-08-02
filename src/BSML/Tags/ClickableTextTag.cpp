#include "BSML/Tags/ClickableTextTag.hpp"
#include "BSML/Components/ClickableText.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"
#include "logging.hpp"
#include "internal_macros.hpp"

#include "HMUI/Touchable.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLTagParser<ClickableTextTag> clickableTextTagParser({"clickable-text"});
    UnityEngine::GameObject* ClickableTextTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Clickable text");
        auto gameObject = GameObject::New_ctor("BSMLClickableText");
        gameObject->SetActive(false);
        gameObject->get_transform()->SetParent(parent, false);

        auto textMesh = gameObject->AddComponent<ClickableText*>();
        textMesh->set_font(Helpers::GetMainTextFont());
        textMesh->set_fontSharedMaterial(Helpers::GetMainUIFontMaterial());
        textMesh->set_text("BSMLClickableText");
        textMesh->set_fontSize(4);
        textMesh->set_color({1.0f, 1.0f, 1.0f, 1.0f});
        textMesh->set_richText(true);

        auto rectTransform = textMesh->get_rectTransform();
        rectTransform->set_anchorMin({0.5f, 0.5f});
        rectTransform->set_anchorMax({0.5f, 0.5f});
        rectTransform->set_sizeDelta({90, 8});
        
        gameObject->AddComponent<UI::LayoutElement*>();

        gameObject->SetActive(true);
        return gameObject;
    }
}