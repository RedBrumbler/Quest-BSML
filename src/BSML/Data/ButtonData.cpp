#include "BSML/Data/ButtonData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"

namespace BSML {
    ButtonData::ButtonData(const tinyxml2::XMLElement& elem) {
        GET_BSML_STRING("on-click", onClick);
        GET_BSML_STRING("click-event", onClick);
        GET_BSML_STRING("event-click", onClick);
        GET_BSML_STRING("method", onClick);
        GET_BSML_STRING("method-name", onClick);
    }
    
    void ButtonData::Apply(UnityEngine::UI::Button* button, Il2CppObject* host) const {
        if (!button || !host) {
            ERROR("nullptr passed to ButtonData::Apply");
            return;
        }
        
        auto methodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onClick.c_str(), 0);
        if (!methodInfo) {
            ERROR("Could not find method '{}' in klass '{}::{}'", onClick, host->klass->namespaze, host->klass->name);
            ERROR("Make sure the name is correct");
        } else {
            // capture by value
            std::function<void()> fun = [methodInfo, host](){ il2cpp_utils::RunMethod(host, methodInfo); };
            auto delegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), fun);
            
            // clear button callbacks
            button->set_onClick(UnityEngine::UI::Button::ButtonClickedEvent::New_ctor());
            // add our callback
            button->get_onClick()->AddListener(delegate);
        }
    }
}