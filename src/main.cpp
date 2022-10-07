#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "logging.hpp"
#include "hooking.hpp"

#include "BSMLDataCache.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"
#include "BSML/Tags/BSMLTag.hpp"

using namespace BSML;

ModInfo modInfo{MOD_ID, VERSION};

extern "C" void setup(ModInfo& info) {
    info = modInfo;
}

static bool isLoaded = false;

extern "C" void load() {
    if (isLoaded) return;
    isLoaded = true;

    if (!LoadConfig())
        SaveConfig();
    custom_types::Register::AutoRegister();
    Hooks::InstallHooks(BSML::Logging::getLogger());
}

BSML_DATACACHE(settings_about) {
    return IncludedAssets::SettingsAbout_bsml;
}

BSML_DATACACHE(mods_idle) {
    return IncludedAssets::mods_idle_png;
}

BSML_DATACACHE(mods_selected) {
    return IncludedAssets::mods_selected_png;
}

BSML_DATACACHE(visibility) {
    return IncludedAssets::visibility_png;
}
