#include "BSML/Components/Keyboard/Key.hpp"
#include "BSML/Components/Keyboard/Keyboard.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/delegates.hpp"

#include "System/StringComparison.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/UIKeyboardKey.hpp"
#include "HMUI/HoverHint.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"

DEFINE_TYPE(BSML, Key);

using namespace Polyglot;
using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    Key Key::Set(StringW value) {
        if (!Il2CppString::IsNullOrEmpty(value))
            this.value = value;
        return *this;
    }

    Key Key::construct() {
        return Key::New_ctor();
    }

    Key Key::construct(Keyboard kb, UnityEngine::Vector2 position, StringW text, float width, float height, UnityEngine::Color color) {
        auto self = construct();
        self.value = text;
        self.kb = kb;

        self.name = text;
        self.button = Button::Instantiate(kb.baseButton, kb.container, false);
        auto button = self.button;
        UnityEngine::Object::Destroy(button.GetComponent<HMUI::UIKeyboardKey>());

        auto localizer = button.GetComponentInChildren<Polyglot::LocalizedTextMeshProUGUI>(true);
        if (localizer) UnityEngine::Object::Destroy(localizer);

        auto textMesh = button.GetComponentInChildren<TMPro::TextMeshProUGUI>(true);
        textMesh.richText = true;

        auto transform = RectTransform(button.transform.convert());
        transform.anchorMin = {0.5f, 0.5f};
        transform.anchorMax{0.5f, 0.5f};

        auto txt = button.GetComponentInChildren<TMPro::TMP_Text>();
        textMesh.enableWordWrapping = false;
        button.transform.localScale = {kb.scale, kb.scale, 1.0f};
        textMesh.fontSize = 5.0f;
        textMesh.text = text;
        button.GetComponentInChildren<Image>().color = color;

        if (width == 0) {
            auto v = txt.GetPreferredValues(text);
            v.x += 10.0f;
            width = v.x;
        }

        position.x += kb.scale * width / 2;
        position.y -= kb.scale * height / 2;

        transform.anchoredPosition = position;
        transform.sizeDelta = {width, height};
        kb.currentPosition.x += width * kb.scale + kb.padding;

        button.onClick = Button::ButtonClickedEvent::New_ctor();

        auto delegate = MakeUnityAction(std::bind(&Key::OnClick, self));
        button.onClick.AddListener(delegate);
        auto hintText = button.gameObject.AddComponent<HMUI::HoverHint>();
        hintText.text = self.value;
        hintText.hoverHintController = Helpers::GetHoverHintController();

        return self;
    }

    void Key::OnClick() {
        // if there is no key action, or the key does not end in %CR%, then just use the value
        if (!KeyAction() && !Enter()) {
            StringW x = kb.shift ? shifted : value;
            if (x == "") x = value;

            if (kb.caps) x = value.ToUpper();

            kb.add_text(x);
        }
        kb.DrawCursor();
    }

    bool Key::KeyAction() {
        if (!keyAction) return false;
        keyAction(this);
        return true;
    }

    bool Key::Enter() {
        if (!value.EndsWith("%%CR%%", System::StringComparison::Ordinal)) return false;
        kb.add_text(value.Substring(0, value.get_Length() - 4));
        kb.Enter(this);
        return true;
    }

    Keyboard Key::get_kb() {
        static constexpr auto offset = Key::___Base__Size + offsetof(___InternalRepresentation, kb);
        return custom_types::read_field<Keyboard>(convert(), offset);
    }

    void Key::set_kb(Keyboard value) {
        static constexpr auto offset = Key::___Base__Size + offsetof(___InternalRepresentation, kb);
        custom_types::write_field<Keyboard>(convert(), offset, std::forward(value));
    }
}
