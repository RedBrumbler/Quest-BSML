#include "BSML/Tags/ListTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/TableView.hpp"
#include "BSML/Components/CustomListTableData.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/ScrollRect.hpp"
#include "UnityEngine/UI/RectMask2D.hpp"
#include "UnityEngine/Canvas.hpp"
#include "HMUI/EventSystemListener.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/TableView_CellsGroup.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLTagParser<ListTag> listTagParser({"list"});
    Canvas* listCanvasTemplate = nullptr;
    UnityEngine::GameObject* ListTag::CreateObject(UnityEngine::Transform* parent) const {
        DEBUG("Creating List");
        auto container = GameObject::New_ctor("BSMLListContainer")->AddComponent<RectTransform*>();
        auto containerGameObject = container->get_gameObject();
        auto layoutElement = containerGameObject->AddComponent<LayoutElement*>();
        containerGameObject->get_transform()->SetParent(parent, false);

        auto gameObject = GameObject::New_ctor("BSMLList");
        gameObject->get_transform()->SetParent(containerGameObject->get_transform(), false);
        gameObject->SetActive(false);

        if (!listCanvasTemplate || !Object::IsNativeObjectAlive(listCanvasTemplate)) {
            listCanvasTemplate = Resources::FindObjectsOfTypeAll<Canvas*>().FirstOrDefault([](auto x){ return x->get_name() == "DropdownTableView"; });
        }

        auto scrollRect = gameObject->AddComponent<ScrollRect*>();
        Utilities::AddComponent(gameObject, listCanvasTemplate);
        gameObject->AddComponent<VRUIControls::VRGraphicRaycaster*>()->physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        gameObject->AddComponent<HMUI::Touchable*>();
        gameObject->AddComponent<HMUI::EventSystemListener*>();

        auto scrollView = gameObject->AddComponent<HMUI::ScrollView*>();
        // TODO: make the custom types for this
        HMUI::TableView* tableView = gameObject->AddComponent<BSML::TableView*>();
        auto tableData = container->get_gameObject()->AddComponent<CustomListTableData*>();
        tableData->tableView = tableView;
        tableView->preallocatedCells = ArrayW<HMUI::TableView::CellsGroup*>(il2cpp_array_size_t(0));
        tableView->isInitialized = false;
        tableView->scrollView = scrollView;

        auto viewPort = GameObject::New_ctor("ViewPort")->AddComponent<RectTransform*>();
        viewPort->SetParent(gameObject->get_transform(), false);
        viewPort->get_gameObject()->AddComponent<RectMask2D*>();
        scrollRect->set_viewport(viewPort);

        auto content = GameObject::New_ctor("Content")->AddComponent<RectTransform*>();
        content->SetParent(viewPort, false);

        scrollView->contentRectTransform = content;
        scrollView->viewport = viewPort;

        viewPort->set_anchorMin({0, 0});
        viewPort->set_anchorMax({1, 1});
        viewPort->set_anchoredPosition({0, 0});
        viewPort->set_sizeDelta({0, 0});

        auto tableViewRectTransform = reinterpret_cast<RectTransform*>(tableView->get_transform());
        tableViewRectTransform->set_anchorMin({0, 0});
        tableViewRectTransform->set_anchorMax({1, 1});
        tableViewRectTransform->set_anchoredPosition({0, 0});
        tableViewRectTransform->set_sizeDelta({0, 0});

        tableView->SetDataSource(tableData->i_IDataSource(), false);
        return containerGameObject;
    }
}
