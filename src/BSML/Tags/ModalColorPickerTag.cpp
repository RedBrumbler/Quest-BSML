#include "BSML/Tags/ModalColorPickerTag.hpp"
#include "BSML.hpp"
#include "BSML/Components/ModalColorPicker.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "logging.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"

#include "HMUI/ImageView.hpp"
#include "System/Action_2.hpp"
#include "BSML/Components/ModalColorPicker.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ModalColorPickerTag> modalColorPickerTagParser({"modal-color-picker"});
    std::string buttonXML {
        "\
        <horizontal anchor-pos-y='-30' spacing='2' horizontal-fit='PreferredSize'>\
            <button text='Cancel' on-click='CancelPressed' pref-width='30'/>\
            <action-button text='Done' on-click='DonePressed' pref-width='30'/>\
        </horizontal>\
        "    
    };

    GlobalNamespace::RGBPanelController* rgbTemplate = nullptr;
    GlobalNamespace::HSVPanelController* hsvTemplate = nullptr;
    HMUI::ImageView* currentColorTemplate = nullptr;

    void ModalColorPickerTag::Construct(UnityEngine::Transform* parent, Il2CppObject* host) const {
        auto go = CreateObject(parent);
        auto externalComponents = go->GetComponent<ExternalComponents*>();
        auto colorPicker = externalComponents->Get<ModalColorPicker*>();
        SetHostField(host, colorPicker);
        
        rectTransformData.Apply(externalComponents->Get<RectTransform*>());
        modalData.Apply(colorPicker->modalView, host);
        modalColorPickerData.Apply(colorPicker, host);

        CreateChildren(go->get_transform(), host);
    }

    UnityEngine::GameObject* ModalColorPickerTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating Modal Color Picker");

        GameObject* gameObject = Base::CreateObject(parent);
        auto externalComponents = gameObject->GetComponent<ExternalComponents*>();
        auto windowTransform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        gameObject->set_name("BSMLModalColorPicker");
        windowTransform->set_sizeDelta({135, 75});

        auto colorPicker = gameObject->AddComponent<ModalColorPicker*>();
        colorPicker->modalView = externalComponents->Get<ModalView*>();

        if (!rgbTemplate || !Object::IsNativeObjectAlive(rgbTemplate)) 
            rgbTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::RGBPanelController*>().FirstOrDefault([](auto x){ return x->get_name() == "RGBColorPicker"; });
        if (!hsvTemplate || !Object::IsNativeObjectAlive(hsvTemplate)) 
            hsvTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::HSVPanelController*>().FirstOrDefault([](auto x){ return x->get_name() == "HSVColorPicker"; });
        if (!currentColorTemplate || !Object::IsNativeObjectAlive(currentColorTemplate)) {
            currentColorTemplate = Resources::FindObjectsOfTypeAll<HMUI::ImageView*>().FirstOrDefault([](auto x){ 
                if (x->get_name() != "SaberColorA") return false;
                auto parent = x->get_transform()->get_parent();
                if (!parent) return false;
                return parent->get_name() == "ColorSchemeView"; 
            });
        }   

        std::function<void(UnityEngine::Color value, GlobalNamespace::ColorChangeUIEventType type)> fun = std::bind(&ModalColorPicker::OnChange, colorPicker, std::placeholders::_1, std::placeholders::_2);
        using delegate_t = System::Action_2<UnityEngine::Color, GlobalNamespace::ColorChangeUIEventType>*;
        auto delegate = il2cpp_utils::MakeDelegate<delegate_t>(classof(delegate_t), fun);
        auto rgbController = Object::Instantiate(rgbTemplate, gameObject->get_transform(), false);
        rgbController->set_name("BSMLRGBPanel");
        auto rgbTransform = reinterpret_cast<RectTransform*>(rgbController->get_transform());
        rgbTransform->set_anchoredPosition({0, 3});
        rgbTransform->set_anchorMin({0, .25f});
        rgbTransform->set_anchorMax({0, .25f});
        colorPicker->rgbPanel = rgbController;
        rgbController->add_colorDidChangeEvent(delegate);

        auto hsvController = Object::Instantiate(hsvTemplate, gameObject->get_transform(), false);
        hsvController->set_name("BSMLHSVPanel");
        auto hsvTransform = reinterpret_cast<RectTransform*>(hsvController->get_transform());
        hsvTransform->set_anchoredPosition({0, 3});
        hsvTransform->set_anchorMin({0.75f, 0.5f});
        hsvTransform->set_anchorMax({0.75f, 0.5f});
        hsvController->add_colorDidChangeEvent(delegate);
        colorPicker->hsvPanel = hsvController;

        auto colorImage = Object::Instantiate(currentColorTemplate, gameObject->get_transform(), false);
        colorImage->set_name("BSMLCurrentColor");
        auto colorTransform = reinterpret_cast<RectTransform*>(colorImage->get_transform());
        colorTransform->set_anchoredPosition({0, 0});
        colorTransform->set_anchorMin({0.5, 0.5f});
        colorTransform->set_anchorMax({0.5, 0.5f});
        colorPicker->colorImage = colorImage;

        BSML::parse_and_construct(buttonXML, gameObject->get_transform(), colorPicker);

        externalComponents->Add(colorPicker);
        return gameObject;
    }

    void ModalColorPickerTag::parse(const tinyxml2::XMLElement& elem) {
        DEBUG("Parsing modal color picker tag");
        this->Base::parse(elem);

        modalColorPickerData = ModalColorPickerData(elem);
    }
}