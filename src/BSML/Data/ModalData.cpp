#include "BSML/Data/ModalData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "System/Action.hpp"

namespace BSML {
    ModalData::ModalData(const tinyxml2::XMLElement& elem) {
        GET_BSML_BOOL_OPT("click-off-closes", clickOffCloses);
        GET_BSML_BOOL_OPT("clickerino-offerino-closerino", clickOffCloses);
        GET_BSML_BOOL_OPT("move-to-center", moveToCenter);

        GET_BSML_STRING("on-blocker-clicked", onBlockerClicked);
    }

    void ModalData::Apply(BSML::ModalView* modal, Il2CppObject* host) const {
        if (!modal || !host) {
            ERROR("nullptr passed to ModalData::Apply");
            return;
        }

        modal->host = host;

        if (get_moveToCenter().has_value()) modal->moveToCenter = get_moveToCenter().value();

        if (get_clickOffCloses().has_value()) modal->dismissOnBlockerClicked = get_clickOffCloses().value();

        modal->onBlockerClicked = il2cpp_functions::class_get_method_from_name(host->klass, onBlockerClicked.c_str(), 0);
        
        std::function<void()> fun = [modal](){
            modal->BlockerClicked();
        }; 
        auto delegate = il2cpp_utils::MakeDelegate<System::Action*>(classof(System::Action*), fun);
        modal->add_blockerClickedEvent(delegate);
    }
}