#include "BSML/Tags/ModalColorPickerTag.hpp"
#include "BSML/Components/ModalColorPicker.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "Helpers/delegates.hpp"
#include "logging.hpp"
#include "BSML.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/GameObject.hpp"

#include "HMUI/ImageView.hpp"
#include "BSML/Components/ModalColorPicker.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ModalColorPickerTag> modalColorPickerTagParser({"modal-color-picker"});
    std::string buttonXML {
        "\
        <horizontal anchor-pos-y='-30' spacing='2' horizontal-fit='PreferredSize'>\
            <button text='Cancel' on-click='CancelPressed' pref-width='30'/>\
            <action-button text='Done' on-click='DonePressed' pref-width='30'/>\
        </horizontal>\
        "
    };

    GlobalNamespace::RGBPanelController get_rgbTemplate() {
        static SafePtrUnity<GlobalNamespace::RGBPanelController> rgbTemplate;
        if (!rgbTemplate)
            rgbTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::RGBPanelController>().FirstOrDefault([](auto x){ return x.name == "RGBColorPicker"; });
        return GlobalNamespace::RGBPanelController(rgbTemplate.ptr());
    }
    GlobalNamespace::HSVPanelController get_hsvTemplate() {
        static SafePtrUnity<GlobalNamespace::HSVPanelController> hsvTemplate;
        if (!hsvTemplate)
            hsvTemplate = Resources::FindObjectsOfTypeAll<GlobalNamespace::HSVPanelController>().FirstOrDefault([](auto x){ return x.name == "HSVColorPicker"; });
        return GlobalNamespace::HSVPanelController(hsvTemplate.ptr());
    }
    HMUI::ImageView get_currentColorTemplate() {
        static SafePtrUnity<HMUI::ImageView> currentColorTemplate;
        if (!currentColorTemplate) {
            currentColorTemplate = Resources::FindObjectsOfTypeAll<HMUI::ImageView>().FirstOrDefault([](auto x){
                if (x.name != "SaberColorA") return false;
                auto parent = x.transform.parent;
                if (!parent) return false;
                return parent.name == "ColorSchemeView";
            });
        }
        return HMUI::ImageView(currentColorTemplate.ptr());
    }

    UnityEngine::GameObject ModalColorPickerTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Modal Color Picker");

        auto gameObject = Base::CreateObject(parent);
        auto externalComponents = gameObject.GetComponent<ExternalComponents>();
        RectTransform windowTransform {gameObject.transform.convert()};
        gameObject.name = "BSMLModalColorPicker";
        windowTransform.sizeDelta = {135, 75};

        auto colorPicker = gameObject.AddComponent<ModalColorPicker>();
        colorPicker.modalView = externalComponents.Get<ModalView>();

        auto onChangeInfo = il2cpp_functions::class_get_method_from_name(static_cast<Il2CppObject*>(colorPicker)->klass, "OnChange", 2);
        auto delegate = MakeSystemAction<UnityEngine::Color, GlobalNamespace::ColorChangeUIEventType>(colorPicker, onChangeInfo);
        auto rgbController = Object::Instantiate(get_rgbTemplate(), gameObject.transform, false);
        rgbController.name = "BSMLRGBPanel";
        RectTransform rgbTransform {rgbController.transform.convert()};
        rgbTransform.anchoredPosition = {0, 3};
        rgbTransform.anchorMin = {0, .25f};
        rgbTransform.anchorMax = {0, .25f};
        colorPicker.rgbPanel = rgbController;
        rgbController.add_colorDidChangeEvent(delegate);

        auto hsvController = Object::Instantiate(get_hsvTemplate(), gameObject.transform, false);
        hsvController.name = "BSMLHSVPanel";
        RectTransform hsvTransform {hsvController.transform.convert()};
        hsvTransform.anchoredPosition = {0, 3};
        hsvTransform.anchorMin = {0.75f, 0.5f};
        hsvTransform.anchorMax = {0.75f, 0.5f};
        hsvController.add_colorDidChangeEvent(delegate);
        colorPicker.hsvPanel = hsvController;

        auto colorImage = Object::Instantiate(get_currentColorTemplate(), gameObject.transform, false);
        colorImage.name = "BSMLCurrentColor";
        RectTransform colorTransform {colorImage.transform.convert()};
        colorTransform.anchoredPosition = {0, 0};
        colorTransform.anchorMin = {0.5, 0.5f};
        colorTransform.anchorMax = {0.5, 0.5f};
        colorPicker.colorImage = colorImage;

        BSML::parse_and_construct(buttonXML, gameObject.transform, colorPicker);

        externalComponents.Add(colorPicker);
        return gameObject;
    }
}
