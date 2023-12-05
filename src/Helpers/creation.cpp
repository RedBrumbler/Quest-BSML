#include "Helpers/creation.hpp"
#include "Helpers/getters.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/CanvasGroup.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/AdditionalCanvasShaderChannels.hpp"
#include "UnityEngine/RenderMode.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace TMPro;

namespace BSML::Helpers {
    TMP_Text CreateText(System::Type type, UnityEngine::Transform parent, StringW text, Vector2 anchoredPosition, Vector2 sizeDelta) {
        auto go = GameObject::New_ctor("CustomUIText");
        go.SetActive(false);

        TMP_Text textComponent{go.AddComponent(type).convert()};
        textComponent.font = GetMainTextFont();
        textComponent.fontSharedMaterial = GetMainUIFontMaterial();
        textComponent.rectTransform.SetParent(parent, false);
        textComponent.text = text;
        textComponent.fontSize = 4;
        textComponent.color = {1.0f, 1.0f, 1.0f, 1.0f};

        auto rectTransform = textComponent.rectTransform;
        rectTransform.anchorMin = {0.5f, 0.5f};
        rectTransform.anchorMax = {0.5f, 0.5f};
        rectTransform.sizeDelta = sizeDelta;
        rectTransform.anchoredPosition = anchoredPosition;

        go.SetActive(true);
        return textComponent;
    }

    SafePtrUnity<Canvas> canvasTemplate;
    HMUI::ViewController CreateViewController(System::Type type) {
        if (!canvasTemplate)
            canvasTemplate = Resources::FindObjectsOfTypeAll<Canvas>().FirstOrDefault([](auto x) { return x.name == "DropdownTableView"; });

        auto go = GameObject::New_ctor(type.Name);
        auto cv = go.AddComponent<Canvas>();

        cv.additionalShaderChannels = canvasTemplate.additionalShaderChannels;
        cv.overrideSorting = canvasTemplate.overrideSorting;
        cv.pixelPerfect = canvasTemplate.pixelPerfect;
        cv.referencePixelsPerUnit = canvasTemplate.referencePixelsPerUnit;
        cv.renderMode = canvasTemplate.renderMode;
        cv.scaleFactor = canvasTemplate.scaleFactor;
        cv.sortingLayerID = canvasTemplate.sortingLayerID;
        cv.sortingOrder = canvasTemplate.sortingOrder;
        cv.worldCamera = canvasTemplate.worldCamera;

        go.AddComponent<VRUIControls::VRGraphicRaycaster>().physicsRaycaster = GetPhysicsRaycasterWithCache();
        go.AddComponent<CanvasGroup>();
        HMUI::ViewController vc{go.AddComponent(type).convert()};

        vc.rectTransform.anchorMin = {0, 0};
        vc.rectTransform.anchorMax = {1, 1};
        vc.rectTransform.sizeDelta = {0, 0};
        vc.rectTransform.anchoredPosition = {0, 0};
        go.SetActive(false);
        return vc;
    }

    HMUI::FlowCoordinator CreateFlowCoordinator(System::Type type) {
        HMUI::FlowCoordinator flow {GameObject::New_ctor(type.Name)->AddComponent(type)};
        flow.baseInputModule = GetMainFlowCoordinator().baseInputModule;
        return flow;
    }

    HMUI::HoverHint AddHoverHint(UnityEngine::GameObject object, StringW text) {
        auto hintText = object.AddComponent<HMUI::HoverHint>();
        hintText.text = text;
        hintText.hoverHintController = GetHoverHintController();
        return hintText;
    }
}
