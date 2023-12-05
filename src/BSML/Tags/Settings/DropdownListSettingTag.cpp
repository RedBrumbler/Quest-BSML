#include "BSML/Tags/Settings/DropdownListSettingTag.hpp"
#include "BSML/Components/ExternalComponents.hpp"
#include "logging.hpp"
#include "Helpers/getters.hpp"

#include "BSML/Components/Settings/DropdownListSetting.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "HMUI/SimpleTextDropdown.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableView_CellsGroup.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<DropdownListSettingTag> dropdownListSettingTagParser({"dropdown-list-setting"});

    GameObject get_dropdownTemplate() {
        static SafePtrUnity<GameObject> dropdownTemplate;
        if (!dropdownTemplate) {
            dropdownTemplate = Resources::FindObjectsOfTypeAll<HMUI::SimpleTextDropdown>().FirstOrDefault([](auto x){
                auto parent = x.transform.parent;
                if (!parent) return false;
                return parent.name == "NormalLevels";
            }).transform.parent.gameObject;
        }
        return GameObject(dropdownTemplate.ptr());
    }

    GameObject get_safePrefab() {
        static SafePtrUnity<GameObject> safePrefab;
        if (!safePrefab) {
            safePrefab = Object::Instantiate(get_dropdownTemplate());
            Object::DontDestroyOnLoad(safePrefab.ptr());
            safePrefab->SetActive(false);
            safePrefab->name = "BSMLDropdownListPrefab";
        }
        return GameObject(safePrefab.ptr());
    }

    UnityEngine::GameObject* DropdownListSettingTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating DropdownListSetting");

        auto gameObject = Object::Instantiate(get_safePrefab(), parent, false);
        RectTransform transform {gameObject.transform.convert()};
        auto externalComponents = gameObject.AddComponent<ExternalComponents>();
        externalComponents.Add(transform);

        gameObject.name = "BSMLDropdownList";
        auto dropdown = gameObject.GetComponentInChildren<HMUI::SimpleTextDropdown>(true);
        auto dropdownGo = dropdown.gameObject;
        dropdownGo.SetActive(false);
        gameObject.SetActive(false);

        dropdown.name = "Dropdown";
        dropdownGo.GetComponentInChildren<VRUIControls::VRGraphicRaycaster>(true).physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        dropdownGo.GetComponentInChildren<HMUI::ModalView>(true)._container = Helpers::GetDiContainer();
        dropdownGo.GetComponentInChildren<HMUI::ScrollView>(true).platformHelper = Helpers::GetIVRPlatformHelper();

        auto labelObject = transform.Find("Label").gameObject;
        Object::Destroy(labelObject.GetComponent<Polyglot::LocalizedTextMeshProUGUI>());

        auto textMesh = labelObject.GetComponent<HMUI::CurvedTextMeshPro>();
        textMesh.text = "BSMLDropdownSetting";
        externalComponents.Add(textMesh);

        auto layoutElement = gameObject.AddComponent<LayoutElement>();
        layoutElement.preferredHeight = 8.0f;
        layoutElement.preferredWidth = 90.0f;
        externalComponents.Add(layoutElement);

        auto dropdownListSetting = dropdownGo.AddComponent<BSML::DropdownListSetting>();
        dropdownListSetting.dropdown = dropdown;
        externalComponents.Add(dropdownListSetting);

        dropdownGo.SetActive(true);
        gameObject.SetActive(true);

        dropdown.tableView.preallocatedCells = Array<HMUI::TableView::CellsGroup>::NewLength(0);
        dropdown.tableView.visibleCells.Clear();

        auto cont = dropdown.transform.Find("DropdownTableView/Viewport/Content");
        int childCount = cont ? cont.childCount : 0;
        for (int i = childCount - 1; i >= 0; i--) {
            cont.GetChild(i).gameObject.SetActive(false);
        }

        return gameObject;
    }
}
