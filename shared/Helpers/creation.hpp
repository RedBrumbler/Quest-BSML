#pragma once

#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"

namespace BSML::Helpers {
    TMPro::TMP_Text* CreateText(System::Type* type, UnityEngine::Transform* parent, StringW text, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta = {60.0f, 10.0f});

    template<typename T = HMUI::CurvedTextMeshPro*>
    requires(std::is_convertible_v<T, TMPro::TMP_Text*>)
    T CreateText(UnityEngine::Transform* parent, StringW text, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta = {60.0f, 10.0f}) {
        return reinterpret_cast<T>(CreateText(reinterpret_cast<System::Type*>(csTypeOf(T)), parent, text, anchoredPosition, sizeDelta));
    }

    HMUI::ViewController* CreateViewController(System::Type* type);

    template<typename T = HMUI::ViewController*>
    requires(std::is_convertible_v<T, HMUI::ViewController*>)
    T CreateViewController() {
        return reinterpret_cast<T>(CreateViewController(reinterpret_cast<System::Type*>(csTypeOf(T))));
    }

    HMUI::FlowCoordinator* CreateFlowCoordinator(System::Type* type);
    
    template<typename T = HMUI::FlowCoordinator*>
    requires(std::is_convertible_v<T, HMUI::FlowCoordinator*>)
    T CreateFlowCoordinator() {
        return reinterpret_cast<T>(CreateFlowCoordinator(reinterpret_cast<System::Type*>(csTypeOf(T))));
    }
}