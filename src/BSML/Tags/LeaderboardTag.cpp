#include "BSML/Tags/LeaderboardTag.hpp"
#include "GlobalNamespace/LeaderboardTableView.hpp"
#include "GlobalNamespace/LeaderboardTableCell.hpp"
#include "GlobalNamespace/LoadingControl.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Object.hpp"
#include "Helpers/getters.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

using namespace UnityEngine;

namespace BSML {
    static BSMLNodeParser<LeaderboardTag> leaderboardTagParser({"leaderboard", "custom-leaderboard"});

    UnityEngine::GameObject* LeaderboardTag::CreateObject(UnityEngine::Transform* parent) const {
        static SafePtrUnity<GlobalNamespace::LeaderboardTableView> leaderboardTemplate;
        if (!leaderboardTemplate) {
            leaderboardTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::LeaderboardTableView*>().First([](auto x) {
                return x->get_name() == "LeaderboardTableView";
            });
        }
        auto table = Object::Instantiate(leaderboardTemplate.ptr(), parent, false);
        table->set_name("BSMLLeaderboard");
        table->cellPrefab->scoreText->set_enableWordWrapping(false);
        table->GetComponent<VRUIControls::VRGraphicRaycaster*>()->physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        for (auto tableCell : table->GetComponentsInChildren<GlobalNamespace::LeaderboardTableCell*>()) 
            UnityEngine::Object::Destroy(tableCell->get_gameObject());
        
        auto loadingControl = table->GetComponentInChildren<GlobalNamespace::LoadingControl*>();
        if (loadingControl) loadingControl->Hide();

        return table->get_gameObject();
    }
}