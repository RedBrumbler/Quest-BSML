#include "BSML/TypeHandlers/ButtonHandler.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"

#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

namespace BSML {
    static ButtonHandler buttonHandler;
    ButtonHandler::Base::PropMap ButtonHandler::get_props() const {
        return {
            {"onClick", {"on-click"}},
            {"clickEvent", {"click-event", "event-click"}}
        };
    }

    ButtonHandler::Base::SetterMap ButtonHandler::get_setters() const {
        return {};
    }

    void ButtonHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto buttonOpt = il2cpp_utils::try_cast<Button>(componentType.component);
        auto host = parserParams.get_host();
        if (buttonOpt.has_value()) {
            auto button = buttonOpt.value();
            auto event = Button::ButtonClickedEvent::New_ctor();

            // it was a button!
            auto onClickItr = componentType.data.find("onClick");
            if (onClickItr != componentType.data.end() && !onClickItr->second.empty()) {
                auto arg = StringParseHelper(onClickItr->second);
                auto onClickMethodInfo = arg.asMethodInfo(host, 0);
                if (onClickMethodInfo) {
                    auto delegate = MakeUnityAction(host, onClickMethodInfo);
                    event->AddListener(delegate);
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", onClickItr->second, host->klass->namespaze, host->klass->name);
                }
            }

            auto clickEventItr = componentType.data.find("click-event");
            if (clickEventItr != componentType.data.end() && !clickEventItr->second.empty()) {
                auto arg = StringParseHelper(clickEventItr->second);
                auto clickEventMethodInfo = arg.asMethodInfo(host, 0);
                if (clickEventMethodInfo) {
                    auto delegate = MakeUnityAction(host, clickEventMethodInfo);
                    event->AddListener(delegate);
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", clickEventItr->second, host->klass->namespaze, host->klass->name);
                }
            }
            button->set_onClick(event);
        }

        Base::HandleType(componentType, parserParams);
    }
}