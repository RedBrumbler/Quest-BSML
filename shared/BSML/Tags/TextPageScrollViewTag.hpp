#pragma once

#include "BSML/Tags/BSMLTag.hpp"
#include "HMUI/ScrollView.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/ReleaseInfoViewController.hpp"
#include "HMUI/TextPageScrollView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "BSML/Components/TextPageScrollViewRefresher.hpp"
using namespace UnityEngine;

namespace BSML {
    class TextPageScrollViewTag : public BSMLTag {
        public:
            TextPageScrollViewTag() : BSMLTag() {}
        protected:
            virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
    };
}