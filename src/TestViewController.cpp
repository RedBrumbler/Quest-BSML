#include "TestViewController.hpp"
#include "logging.hpp"

#include "assets.hpp"
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

        someChoice = StringW(someList[3].convert());
        _myChoice = StringW(someList[0].convert());
    }
    

    void TestViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        
        auto parsed = BSMLDocParser::parse(IncludedAssets::test_xml);
        if (parsed->valid()) {
            INFO("Constructing bsml view");
            parsed->Construct(get_transform(), this);

            INFO("Deleting parsed file pointer");
            delete parsed;
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
}