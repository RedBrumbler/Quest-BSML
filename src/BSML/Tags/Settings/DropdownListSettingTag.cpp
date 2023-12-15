#include "BSML/Tags/Settings/DropdownListSettingTag.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "logging.hpp"
#include "Helpers/getters.hpp"

#include "BSML/Components/Settings/DropdownListSetting.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/SimpleTextDropdown.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<DropdownListSettingTag> dropdownListSettingTagParser({"dropdown-list-setting"});

    GameObject* get_dropdownTemplate() {
        static SafePtrUnity<GameObject> dropdownTemplate;
        if (!dropdownTemplate) {
            dropdownTemplate = Resources::FindObjectsOfTypeAll<HMUI::SimpleTextDropdown*>().FirstOrDefault([](auto x){
                auto parent = x->get_transform()->get_parent();
                if (!parent) return false;
                return parent->get_name() == "NormalLevels";
            })->get_transform()->get_parent()->get_gameObject();
        }
        return dropdownTemplate.ptr();
    }

    GameObject* get_safePrefab() {
        static SafePtrUnity<GameObject> safePrefab;
        if (!safePrefab) {
            safePrefab = Object::Instantiate(get_dropdownTemplate());
            Object::DontDestroyOnLoad(safePrefab.ptr());
            safePrefab->SetActive(false);
            safePrefab->set_name("BSMLDropdownListPrefab");
        }
        return safePrefab.ptr();
    }

    UnityEngine::GameObject* DropdownListSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating DropdownListSetting");

        auto gameObject = Object::Instantiate(get_safePrefab(), parent, false);
        auto transform = reinterpret_cast<RectTransform*>(gameObject->get_transform());
        auto externalComponents = gameObject->AddComponent<ExternalComponents*>();
        externalComponents->Add(transform);

        gameObject->set_name("BSMLDropdownList");
        auto dropdown = gameObject->GetComponentInChildren<HMUI::SimpleTextDropdown*>(true);
        dropdown->get_gameObject()->SetActive(false);
        gameObject->SetActive(false);

        dropdown->set_name("Dropdown");
        dropdown->get_gameObject()->GetComponentInChildren<VRUIControls::VRGraphicRaycaster*>(true)->_physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        dropdown->get_gameObject()->GetComponentInChildren<HMUI::ModalView*>(true)->_container = Helpers::GetDiContainer();
        dropdown->get_gameObject()->GetComponentInChildren<HMUI::ScrollView*>(true)->_platformHelper = Helpers::GetIVRPlatformHelper();

        auto labelObject = transform->Find("Label")->get_gameObject();
        Object::Destroy(labelObject->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());

        auto textMesh = labelObject->GetComponent<HMUI::CurvedTextMeshPro*>();
        textMesh->set_text("BSMLDropdownSetting");
        externalComponents->Add(textMesh);

        auto layoutElement = gameObject->AddComponent<LayoutElement*>();
        layoutElement->set_preferredHeight(8.0f);
        layoutElement->set_preferredWidth(90.0f);
        externalComponents->Add(layoutElement);

        auto dropdownListSetting = dropdown->get_gameObject()->AddComponent<BSML::DropdownListSetting*>();
        dropdownListSetting->dropdown = dropdown;
        externalComponents->Add(dropdownListSetting);

        dropdown->get_gameObject()->SetActive(true);
        gameObject->SetActive(true);

        dropdown->_tableView->_preallocatedCells = Array<HMUI::TableView::CellsGroup*>::NewLength(0);
        dropdown->_tableView->_visibleCells->Clear();

        auto cont = dropdown->get_transform()->Find("DropdownTableView/Viewport/Content");
        int childCount = cont ? cont->get_childCount() : 0;
        for (int i = childCount - 1; i >= 0; i--) {
            cont->GetChild(i)->get_gameObject()->SetActive(false);
        }

        return gameObject;
    }
}
