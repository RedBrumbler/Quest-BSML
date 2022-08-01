#include "TestViewController.hpp"
#include "logging.hpp"

#include "assets.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/Touchable.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

DEFINE_TYPE(BSML, TestViewController);

namespace BSML {
    void TestViewController::ctor() {
        someList = List<StringW>::New_ctor();
        
        someList->Add("Hello");
        someList->Add("I");
        someList->Add("Think");
        someList->Add("Pink");
        someList->Add("Is");
        someList->Add("Cute");

        _myChoice = StringW(someList[3]);

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
    }
    

    void TestViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        
        get_gameObject()->AddComponent<HMUI::Touchable*>();
        auto parsed = BSMLDocParser::parse(IncludedAssets::test_xml);
        if (parsed->valid()) {
            INFO("Constructing bsml view");
            parsed->Construct(get_transform(), this);
        } else {
            ERROR("Invalid BSML file");
        }

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

    void TestViewController::testToggle_changed(bool value) {
        INFO("testToggle changed: {}, was: {}", value, _testToggle);
    }

    void TestViewController::myChoice_changed(StringW value) {
        if (!_myChoice) {
            INFO("myChoice changed: {}", value);
        } else {
            INFO("myChoice changed: {}, was: {}", value, _myChoice);
        }
    }

    void TestViewController::incdecValue_changed(float value) {
        INFO("incdecValue changed: {}, was: {}", value, _incdecValue);
    }

    void TestViewController::PinkCuteToggled(bool value) {
        INFO("PinkCuteToggled: {}", value);
    }

    float TestViewController::get_length() { return _length; }
    void TestViewController::set_length(float value) { _length = value; INFO("length set"); }


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
}