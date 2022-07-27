#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logging.hpp"
#include "hooking.hpp"

#include "assets.hpp"
#include "BSMLDataCache.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

#include "questui/shared/QuestUI.hpp"
#include "TestViewController.hpp"

using namespace BSML;

ModInfo modInfo{MOD_ID, VERSION};

extern "C" void setup(ModInfo& info) {
    info = modInfo;
}

static bool isLoaded = false;

extern "C" void load() {
    if (isLoaded) return;
    isLoaded = true;
    custom_types::Register::AutoRegister();
    
    Hooks::InstallHooks(BSML::Logging::getLogger());

    QuestUI::Register::RegisterAllModSettingsViewController<BSML::TestViewController*>(modInfo, "BSMLTest");
}