#include "scotland2/shared/loader.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "hooking.hpp"
#include "logging.hpp"

#include "BSMLDataCache.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "custom-types/shared/register.hpp"

namespace BSML {}
using namespace BSML;

modloader::ModInfo modInfo{MOD_ID, VERSION, GIT_COMMIT};

namespace BSML {
    Logger& Logging::getLogger() {
        static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
        return *logger;
    }
}

extern "C" void setup(CModInfo* info) {
    info->version = VERSION;
    info->id = MOD_ID;
    info->version_long = GIT_COMMIT;

    modInfo.assign(*info);
}

static bool isLoaded = false;

extern "C" void load() {
    if (isLoaded) return;
    isLoaded = true;

    INFO("Loading BSML built from branch '" GIT_BRANCH "' and commit {}", GIT_COMMIT);

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
