#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logging.hpp"

#include "assets.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

#include "questui/shared/QuestUI.hpp"
using namespace BSML;

ModInfo modInfo{MOD_ID, VERSION};

extern "C" void setup(ModInfo& info) {
    info = modInfo;
}

static bool isLoaded = false;

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool, bool) {
    if (!firstActivation) return;

    auto parsed = BSMLDocParser::parse(IncludedAssets::test_xml);
    if (parsed->valid()) {
        INFO("Constructing bsml view");
        parsed->Construct(self->get_transform(), self);
        INFO("Deleting parsed file pointer");
        delete parsed;
    } else {
        ERROR("Invalid BSML file");
    }
}

extern "C" void load() {
    if (isLoaded) return;
    isLoaded = true;

    QuestUI::Register::RegisterAllModSettingsViewController(modInfo, "BSMLTest", DidActivate);
}