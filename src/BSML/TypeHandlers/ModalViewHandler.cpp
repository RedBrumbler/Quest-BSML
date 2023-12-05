#include "BSML/TypeHandlers/ModalViewHandler.hpp"

namespace BSML {
    static ModalViewHandler modalViewHandler{};

    ModalViewHandler::Base::PropMap ModalViewHandler::get_props() const {
        return {
            {"id", {"id"}},
            {"showEvent", {"show-event"}},
            {"hideEvent", {"hide-event"}},
            {"clickOffCloses", {"click-off-closes", "clickerino-offerino-closerino"}},
            {"moveToCenter", {"move-to-center"}}
        };
    }

    ModalViewHandler::Base::SetterMap ModalViewHandler::get_setters() const {
        return {
            {"clickOffCloses", [](auto component, auto value){ component.dismissOnBlockerClicked = value; }},
            {"moveToCenter", [](auto component, auto value){ component.moveToCenter = value; }},
        };
    }

    void ModalViewHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        BSML::ModalView modalView {componentType.component.convert()};
        auto& data = componentType.data;

        auto showEventItr = data.find("showEvent");
        if (showEventItr != data.end()) {
            parserParams.AddEvent(showEventItr->second, [modalView = modalView.convert()](){ BSML::ModalView(modalView).Show(); });
        }

        auto hideEventItr = data.find("hideEvent");
        if (hideEventItr != data.end()) {
            parserParams.AddEvent(hideEventItr->second, [modalView = modalView.convert()](){ BSML::ModalView(modalView).Hide(); });
        }

        auto idItr = data.find("id");
        if (idItr != data.end()) {
            std::string id = idItr->second;
            auto showMinfo = il2cpp_utils::FindMethodUnsafe(modalView, "Show", 0);
            auto hideMinfo = il2cpp_utils::FindMethodUnsafe(modalView, "Hide", 0);

            if (showMinfo) parserParams.AddAction(id + "#Show", new BSMLAction(modalView, showMinfo));
            if (hideMinfo) parserParams.AddAction(id + "#Hide", new BSMLAction(modalView, hideMinfo));
        }
        Base::HandleType(componentType, parserParams);
    }
}
