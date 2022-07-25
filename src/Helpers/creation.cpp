#include "Helpers/creation.hpp"
#include "Helpers/getters.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"

using namespace UnityEngine;
using namespace TMPro;

namespace BSML::Helpers {
    TMP_Text* CreateText(System::Type* type, Transform* parent, StringW text, Vector2 anchoredPosition, Vector2 sizeDelta) {
        auto gameObj = GameObject::New_ctor("CustomUIText");
        gameObj->SetActive(false);

        auto textComponent = reinterpret_cast<TMP_Text*>(gameObj->AddComponent(type));
        textComponent->set_font(GetMainTextFont());
        textComponent->set_fontSharedMaterial(GetMainUIFontMaterial());
        textComponent->get_rectTransform()->SetParent(parent, false);
        textComponent->set_text(text);
        textComponent->set_fontSize(4);
        textComponent->set_color({1.0f, 1.0f, 1.0f, 1.0f});

        auto rectTransform = textComponent->get_rectTransform();
        rectTransform->set_anchorMin({0.5f, 0.5f});
        rectTransform->set_anchorMax({0.5f, 0.5f});
        rectTransform->set_sizeDelta(sizeDelta);
        rectTransform->set_anchoredPosition(anchoredPosition);

        gameObj->SetActive(true);
        return textComponent;
    }
}