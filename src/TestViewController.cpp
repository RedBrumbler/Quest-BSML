#include "TestViewController.hpp"
#include "logging.hpp"

#include "assets.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/Touchable.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Parsing/BSMLParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

DEFINE_TYPE(BSML, TestViewController);

namespace BSML {
    void TestViewController::ctor() {
        someOtherField = false;
        someList = List<StringW>::New_ctor();
        
        someList->Add("Hello");
        someList->Add("I");
        someList->Add("Think");
        someList->Add("Pink");
        someList->Add("Is");
        someList->Add("Cute");

        set_length(5.0f);

        sliderList = List<StringW>::New_ctor();
        sliderList->Add("Never");
        sliderList->Add("Gonna");
        sliderList->Add("Give");
        sliderList->Add("You");
        sliderList->Add("Up");
        sliderChoice = sliderList[3];

        listData = List<CustomCellInfo*>::New_ctor();
        listData->EnsureCapacity(26);

        char letter = 'A';
        for (int i = 0; i < 26; i++) {
            listData->Add(CustomCellInfo::construct(fmt::format("Letter {}", letter), "A good letter"));
            letter++;
        }

        customListData = List<Il2CppObject*>::New_ctor();
        for (int i = 0; i < 20; i++) customListData->Add(CustomListObject::New_ctor());
    }


    void TestViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        
        get_gameObject()->AddComponent<HMUI::Touchable*>();
        auto parser = BSMLParser::parse(IncludedAssets::test_xml);
        parser->Construct(get_transform(), this);

        INFO("this ptr  : {}", fmt::ptr(this));
        INFO("layout ptr: {}", fmt::ptr(layout));
        INFO("button ptr: {}", fmt::ptr(goodButton));
    }

    void TestViewController::ButtonPressed() {
        INFO("Button pressed: {}", fmt::ptr(this));
    }

    void TestViewController::OnPropertiesChanged() {
        INFO("someOtherField: {}", someOtherField);
        INFO("A property changed!");
    }

    void TestViewController::PinkCuteToggled(bool value) {
        INFO("PinkCuteToggled: {}", value);
    }

    float TestViewController::get_length() { return _length; }
    void TestViewController::set_length(float value) { _length = value; INFO("length set {}", value); }


    void TestViewController::ChangeLength(float value) {
        INFO("Length changed: {}\nBacking Value: {}", value, _length);
    }

    void TestViewController::GibString(StringW value) {
        INFO("GibString: {}", value);
    }

    void TestViewController::GibColor(UnityEngine::Color value) {
        INFO("Got color: (r:{}, g:{}, b:{}, a:{})", value.r, value.g, value.b, value.a);
    }

    void TestViewController::TextClick() {
        INFO("Text was clicked!");
    }


    void TestViewController::ShowListModal() {
        listModal->Show();
    }

    void TestViewController::ListElementSelected(HMUI::TableView*, int idx) {
        INFO("List element selected: {}", idx);
    }

    void TestViewController::SegmentedControlSelect(Il2CppObject* segmentedControl, int index) {
        INFO("SegmentedControlSelect: {}", index);
    }
}