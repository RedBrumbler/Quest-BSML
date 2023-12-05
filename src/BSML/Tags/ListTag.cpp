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
#include "UnityEngine/RenderMode.hpp"
#include "UnityEngine/AdditionalCanvasShaderChannels.hpp"
#include "HMUI/EventSystemListener.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/TableView_CellsGroup.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace BSML {
    static BSMLNodeParser<ListTag> listTagParser({"list"});
    Canvas get_listCanvasTemplate() {
        static SafePtrUnity<Canvas> listCanvasTemplate;
        if (!listCanvasTemplate) {
            listCanvasTemplate = Resources::FindObjectsOfTypeAll<Canvas>().FirstOrDefault([](auto x){ return x.name == "DropdownTableView"; });
        }
        return Canvas(listCanvasTemplate.ptr());
    }

    UnityEngine::GameObject ListTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating List");
        auto container = GameObject::New_ctor("BSMLListContainer").AddComponent<RectTransform>();
        auto containerGameObject = container.gameObject;
        auto layoutElement = containerGameObject.AddComponent<LayoutElement>();
        containerGameObject.transform.SetParent(parent, false);

        auto gameObject = GameObject::New_ctor("BSMLList");
        gameObject.transform.SetParent(containerGameObject.transform, false);
        gameObject.SetActive(false);

        auto listCanvasTemplate = get_listCanvasTemplate();
        auto scrollRect = gameObject.AddComponent<ScrollRect>();
        auto canvas = gameObject.AddComponent<Canvas>();
        // using this method causes the list to have it's cells be squished:
        //Utilities::AddComponent(gameObject, listCanvasTemplate);
        // therefore we just copy what we need:
        canvas.additionalShaderChannels = listCanvasTemplate.additionalShaderChannels;
        canvas.overrideSorting = listCanvasTemplate.overrideSorting;
        canvas.pixelPerfect = listCanvasTemplate.pixelPerfect;
        canvas.referencePixelsPerUnit = listCanvasTemplate.referencePixelsPerUnit;
        canvas.renderMode = listCanvasTemplate.renderMode;
        canvas.scaleFactor = listCanvasTemplate.scaleFactor;
        canvas.sortingLayerID = listCanvasTemplate.sortingLayerID;
        canvas.sortingOrder = listCanvasTemplate.sortingOrder;
        canvas.worldCamera = listCanvasTemplate.worldCamera;

        gameObject.AddComponent<VRUIControls::VRGraphicRaycaster>().physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        gameObject.AddComponent<HMUI::Touchable>();
        gameObject.AddComponent<HMUI::EventSystemListener>();

        auto scrollView = gameObject.AddComponent<HMUI::ScrollView>();

        auto tableView = gameObject.AddComponent<BSML::TableView>();
        auto tableData = container.gameObject.AddComponent<CustomListTableData>();
        tableData.tableView = tableView;

        tableView.preallocatedCells = ArrayW<HMUI::TableView::CellsGroup>(il2cpp_array_size_t(0));
        tableView.isInitialized = false;
        tableView.scrollView = scrollView;

        auto viewPort = GameObject::New_ctor("ViewPort").AddComponent<RectTransform>();
        viewPort.SetParent(gameObject.transform, false);
        viewPort.gameObject.AddComponent<RectMask2D>();
        scrollRect.viewport = viewPort;

        auto content = GameObject::New_ctor("Content").AddComponent<RectTransform>();
        content.SetParent(viewPort, false);

        scrollView.contentRectTransform = content;
        scrollView.viewport = viewPort;

        viewPort.anchorMin = {0, 0};
        viewPort.anchorMax = {1, 1};
        viewPort.anchoredPosition = {0, 0};
        viewPort.sizeDelta = {0, 0};

        RectTransform tableViewRectTransform {tableView.transform.convert()};
        tableViewRectTransform.anchorMin = {0, 0};
        tableViewRectTransform.anchorMax = {1, 1};
        tableViewRectTransform.anchoredPosition = {0, 0};
        tableViewRectTransform.sizeDelta = {0, 0};

        tableView.SetDataSource(tableData, false);
        return containerGameObject;
    }
}
