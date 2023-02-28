#include "BSML/Tags/ModalTag.hpp"
#include "BSML/Components/ModalView.hpp"
#include "BSML/Components/ExternalComponents.hpp"

#include "Helpers/getters.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/ScrollRect.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/EventSystemListener.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace VRUIControls;

namespace BSML {
    static BSMLNodeParser<ModalTag> modalTagParser({"modal"});

    HMUI::ModalView* get_modalViewTemplate() {
        static SafePtrUnity<HMUI::ModalView> modalViewTemplate;
        if (!modalViewTemplate) {
            modalViewTemplate = Resources::FindObjectsOfTypeAll<HMUI::ModalView*>().FirstOrDefault([](auto x){ return x->get_gameObject()->get_name() == "DropdownTableView"; });
        }
        return modalViewTemplate.ptr();
    }

    UnityEngine::GameObject* ModalTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Modal");
        auto modalViewTemplate = get_modalViewTemplate();
        auto copy = Object::Instantiate(modalViewTemplate, parent, false);
        auto gameObject = copy->get_gameObject();
        gameObject->SetActive(false);
        gameObject->set_name("BSMLModalView");
        // we use our own custom modalView type, this differs from PC BSML but it just makes it easier to set things up
        auto modalView = gameObject->AddComponent<BSML::ModalView*>();

        
        modalView->presentPanelAnimations = modalViewTemplate->presentPanelAnimations;
        modalView->dismissPanelAnimation = modalViewTemplate->dismissPanelAnimation;
        modalView->container = Helpers::GetDiContainer();
        gameObject->GetComponent<VRGraphicRaycaster*>()->physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        
        Object::DestroyImmediate(gameObject->GetComponent<TableView*>());
        Object::DestroyImmediate(gameObject->GetComponent<ScrollRect*>());
        Object::DestroyImmediate(gameObject->GetComponent<ScrollView*>());
        Object::DestroyImmediate(gameObject->GetComponent<EventSystemListener*>());
        
        auto rectTransform = reinterpret_cast<RectTransform*>(modalView->get_transform());
        int childCount = rectTransform->get_childCount();

        for (int i = 0; i < childCount; i++) {
            auto child = reinterpret_cast<RectTransform*>(rectTransform->GetChild(i));
            DEBUG("child name: {}", child->get_name());

            if (child->get_name() == "BG") {
                DEBUG("twas BG");
                child->set_anchoredPosition({0, 0});
                child->set_sizeDelta({0, 0});
                child->GetComponent<Image*>()->set_raycastTarget(true);
                child->get_gameObject()->SetActive(true);
            } else {
                DEBUG("Destroyed!");
                Object::Destroy(child->get_gameObject());
            }
        }

        rectTransform->set_anchorMin({.5f, .5f});
        rectTransform->set_anchorMax({.5f, .5f});
        rectTransform->set_sizeDelta({0, 0});

        auto externalComponents = gameObject->AddComponent<BSML::ExternalComponents*>();
        externalComponents->Add(rectTransform);
        externalComponents->Add(modalView);

        return gameObject;
    }
}