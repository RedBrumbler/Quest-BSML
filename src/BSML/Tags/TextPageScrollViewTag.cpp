#include "BSML/Tags/TextPageScrollViewTag.hpp"
#include "Helpers/getters.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "BSML/Components/TextPageScrollViewRefresher.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/TextPageScrollView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/ReleaseInfoViewController.hpp"

namespace BSML {
    static BSMLNodeParser<TextPageScrollViewTag> textPageScrollViewTagParser({"text-page", "page"});

    HMUI::TextPageScrollView get_textPageTemplate() {
        static SafePtrUnity<HMUI::TextPageScrollView> textPageTemplate;
        if (!textPageTemplate) {
            textPageTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::ReleaseInfoViewController>().First().textPageScrollView;
        }
        return HMUI::TextPageScrollView(textPageTemplate.ptr());
    }

    UnityEngine::GameObject TextPageScrollViewTag::CreateObject(UnityEngine::Transform parent) const {

        auto scrollView = UnityEngine::Object::Instantiate(get_textPageTemplate(), parent);

        scrollView.name = "BSMLTextScrollPageView";
        scrollView.enabled = true;

        scrollView.platformHelper = Helpers::GetIVRPlatformHelper();

        auto textMesh = scrollView.text;
        textMesh.text = "Default Text";

        textMesh.gameObject.AddComponent<BSML::TextPageScrollViewRefresher>().scrollView = scrollView;

        auto externalComponents = scrollView.gameObject.AddComponent<ExternalComponents>();

        externalComponents.Add(textMesh);

        return scrollView.gameObject;
    }
}
