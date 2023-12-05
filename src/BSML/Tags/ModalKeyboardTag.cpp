#include "BSML/Tags/ModalKeyboardTag.hpp"
#include "BSML/Components/ModalView.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/ScrollRect.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/EventSystemListener.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

#include "BSML/Components/Keyboard/ModalKeyboard.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace VRUIControls;

namespace BSML {
    static BSMLNodeParser<ModalKeyboardTag> modalKeyboardTagParser({"modal-keyboard"});
    UnityEngine::GameObject ModalKeyboardTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Modal Keyboard");
        auto gameObject = ModalTag::CreateObject(parent);
        RectTransform transform { gameObject.transform.convert() };
        gameObject.name = "BSMLModalKeyboard";
        transform.sizeDelta = {135, 75};

        auto parentTransform = GameObject::New_ctor("KeyboardParent").AddComponent<RectTransform>();
        parentTransform.SetParent(transform, false);
        parentTransform.localScale = parentTransform.localScale * 1.4f;
        auto keyboard = Keyboard::construct(parentTransform, Keyboard::QWERTY, true, 4, -12);

        auto modalKeyboard = gameObject.AddComponent<ModalKeyboard>();
        modalKeyboard.keyboard = keyboard;
        modalKeyboard.modalView = gameObject.GetComponent<BSML::ModalView>();
        keyboard.enterPressed = [kb = modalKeyboard.convert()](auto p){ ModalKeyboard(kb).OnEnter(p); };

        auto externalComponents = gameObject.GetComponent<ExternalComponents>();
        externalComponents.Add(modalKeyboard);

        return gameObject;
    }
}
