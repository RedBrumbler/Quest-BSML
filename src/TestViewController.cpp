#include "TestViewController.hpp"
#include "logging.hpp"

#include "assets.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

DEFINE_TYPE(BSML, TestViewController);

namespace BSML {
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
        INFO("testToggle changed: {}, was: {}", value, bsml_testToggle);
    }
}