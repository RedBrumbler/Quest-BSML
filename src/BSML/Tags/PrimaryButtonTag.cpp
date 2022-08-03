#include "BSML/Tags/PrimaryButtonTag.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Resources.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<PrimaryButtonTag> primaryButtonTagParser({"action-button", "primary-button"});
    Button* playButtonPrefab = nullptr;
    Button* PrimaryButtonTag::get_buttonPrefab() const {
        if (!playButtonPrefab || !Object::IsNativeObjectAlive(playButtonPrefab)) {
            playButtonPrefab = Resources::FindObjectsOfTypeAll<Button*>().LastOrDefault([&](auto x){ return x->get_name() == "PlayButton"; });
        }
        return playButtonPrefab;
    }
}