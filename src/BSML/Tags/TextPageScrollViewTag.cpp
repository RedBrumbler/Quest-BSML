#include "BSML/Tags/TextPageScrollViewTag.hpp"
#include "Helpers/getters.hpp"
#include "BSML/Components/ExternalComponents.hpp"

namespace BSML {
    static BSMLTagParser<TextPageScrollViewTag> textPageScrollViewTagParser({"text-page", "page"});
    HMUI::TextPageScrollView* textPageTemplate = nullptr;
    UnityEngine::GameObject* TextPageScrollViewTag::CreateObject(UnityEngine::Transform* parent) const {
        if (textPageTemplate == nullptr) {
            textPageTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::ReleaseInfoViewController*>().First()->textPageScrollView;
        }

        HMUI::TextPageScrollView* scrollView = UnityEngine::Object::Instantiate(textPageTemplate, parent);

        scrollView->set_name("BSMLTextScrollPageView");
        scrollView->set_enabled(true);

        scrollView->platformHelper = Helpers::GetIVRPlatformHelper();

        TMPro::TextMeshProUGUI* textMesh = scrollView->text;
        textMesh->set_text("Default Text");

        textMesh->get_gameObject()->AddComponent<BSML::TextPageScrollViewRefresher*>()->scrollView = scrollView;

        auto externalComponents = scrollView->get_gameObject()->AddComponent<ExternalComponents*>();

        externalComponents->Add(textMesh);

        return scrollView->get_gameObject();
    }
}