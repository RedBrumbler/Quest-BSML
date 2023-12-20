#include "BSML-Lite/Creation/Misc.hpp"

#include "Helpers/getters.hpp"
#include "Helpers/creation.hpp"

#define protected public
#include "BSML/Tags/TextSegmentedControlTag.hpp"
#undef protected

#include "UnityEngine/RectTransform.hpp"
#include "System/Action_2.hpp"

namespace BSML::Lite {
    HMUI::HoverHint* AddHoverHint(const GameObjectWrapper& parent, StringW text) {
        return BSML::Helpers::AddHoverHint(parent, text);
    }

    BSML::FloatingScreen* CreateFloatingScreen(UnityEngine::Vector2 screenSize, UnityEngine::Vector3 position, UnityEngine::Vector3 rotation, float curvatureRadius, bool hasBackground, bool createHandle, BSML::Side handleSide) {
        auto screen = BSML::FloatingScreen::CreateFloatingScreen(screenSize, createHandle, position, UnityEngine::Quaternion::Euler(rotation), curvatureRadius, hasBackground);
        screen->set_HandleSide(handleSide);

        return screen;
    }

    BSML::ProgressBar* CreateProgressBar(UnityEngine::Vector3 position, UnityEngine::Vector3 rotation, UnityEngine::Vector3 scale, StringW headerText, StringW subText1, StringW subText2) {
        return BSML::ProgressBar::CreateProgressBar(position, scale, rotation, headerText, subText1, subText2);
    }

    HMUI::TextSegmentedControl* CreateTextSegmentedControl(const TransformWrapper& parent, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, std::initializer_list<std::string_view> values, std::function<void(int)> onCellWithIdxClicked) {
        auto go = BSML::TextSegmentedControlTag{}.CreateObject(parent);
        auto textSegmentedControl = go->GetComponent<HMUI::TextSegmentedControl*>();

        auto rect = reinterpret_cast<UnityEngine::RectTransform*>(go->get_transform());
        rect->set_anchoredPosition(anchoredPosition);
        rect->set_sizeDelta(sizeDelta);

        ListW<StringW> texts = List<StringW>::New_ctor();
        texts->EnsureCapacity(values.size());
        for (const auto& text : values) texts->Add(text);
        textSegmentedControl->SetTexts(*texts);

        if (onCellWithIdxClicked) {
            textSegmentedControl->add_didSelectCellEvent(
                custom_types::MakeDelegate<System::Action_2<HMUI::SegmentedControl*, int>*>(
                    std::function<void(HMUI::SegmentedControl*, int)>( [onCellWithIdxClicked](HMUI::SegmentedControl* _, int idx) { onCellWithIdxClicked(idx); } )
                )
            );
        }

        return textSegmentedControl;
    }
}
