#include "BSML/TypeHandlers/ScrollableContainerHandler.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "HMUI/ItemForFocussedScrolling.hpp"

namespace BSML {
    static ScrollableContainerHandler scrollableContainerHandler{};

    ScrollableContainerHandler::Base::PropMap ScrollableContainerHandler::get_props() const {
        return {
            {"id", {"id"}},
            {"maskOverflow", {"mask-overflow"}},
            {"alignBottom", { "align-bottom"}},
        };
    }

    ScrollableContainerHandler::Base::SetterMap ScrollableContainerHandler::get_setters() const {
        return {
            {"maskOverflow", [](auto component, auto value){ component->set_maskOverflow(value); }},
            {"alignBottom", [](auto component, auto value){ component->set_alignBottom(value); }}
        };
    }

    void ScrollableContainerHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        Base::HandleType(componentType, parserParams);
        auto scrollView = reinterpret_cast<ScrollableContainer*>(componentType.component);
        auto& data = componentType.data;
        auto idItr = data.find("id");
        if (idItr != data.end() && !idItr->second.empty()) {
            // TODO: scrollView#PageUp thing
        }
    }

    void ScrollableContainerHandler::HandleTypeAfterChildren(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto& gos = parserParams.GetObjectsWithTag("ScrollFocus");
        for (auto go : gos) {
            go->AddComponent<HMUI::ItemForFocussedScrolling*>();
        }
    }

    void ScrollableContainerHandler::HandleTypeAfterParse(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        INFO("After parse");
        auto scrollView = reinterpret_cast<ScrollableContainer*>(componentType.component);
        auto& data = componentType.data;

        auto idItr = data.find("id");
        if (idItr != data.end() && !idItr->second.empty()) {
            auto pageUpButtons = parserParams.GetObjectsWithTag("PageUpFor:" + idItr->second);
            for (auto pageUp : pageUpButtons) {
                scrollView->pageUpButton = pageUp->GetComponent<UnityEngine::UI::Button*>();
                if (scrollView->pageUpButton) break;
            }

            auto pageDownButtons = parserParams.GetObjectsWithTag("PageDownFor:" + idItr->second);
            for (auto pageDown : pageDownButtons) {
                scrollView->pageDownButton = pageDown->GetComponent<UnityEngine::UI::Button*>();
                if (scrollView->pageDownButton) break;
            }

            auto scrollIndicators = parserParams.GetObjectsWithTag("IndicatorFor:" + idItr->second);
            for (auto scrollIndicator : scrollIndicators) {
                scrollView->verticalScrollIndicator = scrollIndicator->GetComponent<HMUI::VerticalScrollIndicator*>();
                if (scrollView->verticalScrollIndicator) break;
            }
            INFO("upButton: {}", fmt::ptr(scrollView->pageUpButton));
            INFO("downButton: {}", fmt::ptr(scrollView->pageDownButton));
            INFO("scrollIndicator: {}", fmt::ptr(scrollView->verticalScrollIndicator));
        }

        scrollView->RefreshContent();
        scrollView->RefreshButtons();
    }
}