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

    HMUI::ModalView get_modalViewTemplate() {
        static SafePtrUnity<HMUI::ModalView> modalViewTemplate;
        if (!modalViewTemplate) {
            modalViewTemplate = Resources::FindObjectsOfTypeAll<HMUI::ModalView>().FirstOrDefault([](auto x){ return x.gameObject.name == "DropdownTableView"; });
        }
        return HMUI::ModalView(modalViewTemplate.ptr());
    }

    UnityEngine::GameObject ModalTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Modal");
        auto modalViewTemplate = get_modalViewTemplate();
        auto copy = Object::Instantiate(modalViewTemplate, parent, false);
        auto gameObject = copy.gameObject;
        gameObject.SetActive(false);
        gameObject.name = "BSMLModalView";
        // we use our own custom modalView type, this differs from PC BSML but it just makes it easier to set things up
        auto modalView = gameObject.AddComponent<BSML::ModalView>();


        modalView._presentPanelAnimations = modalViewTemplate._presentPanelAnimations;
        modalView._dismissPanelAnimation = modalViewTemplate._dismissPanelAnimation;
        modalView._container = Helpers::GetDiContainer();
        gameObject.GetComponent<VRGraphicRaycaster>().physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();

        Object::DestroyImmediate(gameObject.GetComponent<TableView>());
        Object::DestroyImmediate(gameObject.GetComponent<ScrollRect>());
        Object::DestroyImmediate(gameObject.GetComponent<ScrollView>());
        Object::DestroyImmediate(gameObject.GetComponent<EventSystemListener>());

        RectTransform rectTransform {modalView.transform.convert()};
        int childCount = rectTransform.childCount;

        for (int i = 0; i < childCount; i++) {
            RectTransform child { rectTransform.GetChild(i).convert() };
            DEBUG("child name: {}", child.name);

            if (child.name == "BG") {
                DEBUG("twas BG");
                child.anchoredPosition = {0, 0};
                child.sizeDelta = {0, 0};
                child.GetComponent<Image>().raycastTarget = true;
                child.gameObject.SetActive(true);
            } else {
                DEBUG("Destroyed!");
                Object::Destroy(child.gameObject);
            }
        }

        rectTransform.anchorMin = {.5f, .5f};
        rectTransform.anchorMax = {.5f, .5f};
        rectTransform.sizeDelta = {0, 0};

        auto externalComponents = gameObject.AddComponent<BSML::ExternalComponents>();
        externalComponents.Add(rectTransform);
        externalComponents.Add(modalView);

        return gameObject;
    }
}
