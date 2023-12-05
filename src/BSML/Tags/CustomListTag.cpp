#include "BSML/Tags/CustomListTag.hpp"
#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#include "logging.hpp"

#include "BSML/Components/TableView.hpp"
#include "BSML/Components/CustomCellListTableData.hpp"

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
    static BSMLNodeParser<CustomListTag> customListTagParser({"custom-list"});

    Canvas get_customListCanvasTemplate() {
        static SafePtrUnity<Canvas> customListCanvasTemplate;
        if (!customListCanvasTemplate) {
            customListCanvasTemplate = Resources::FindObjectsOfTypeAll<Canvas>().FirstOrDefault([](auto x){ return x.name == "DropdownTableView"; });
        }
        return Canvas(customListCanvasTemplate.ptr());
    }

    UnityEngine::GameObject CustomListTag::CreateObject(UnityEngine::Transform parent) const {
        DEBUG("Creating Custom List");
        auto container = GameObject::New_ctor("BSMLCustomListContainer").AddComponent<RectTransform>();
        auto containerGameObject = container.gameObject;
        auto layoutElement = containerGameObject.AddComponent<LayoutElement>();
        containerGameObject.transform.SetParent(parent, false);

        auto gameObject = GameObject::New_ctor("BSMLCustomList");
        gameObject.transform.SetParent(containerGameObject.transform, false);
        gameObject.SetActive(false);

        auto customListCanvasTemplate = get_customListCanvasTemplate();
        auto scrollRect = gameObject.AddComponent<ScrollRect>();
        auto canvas = gameObject.AddComponent<Canvas>();
        canvas.additionalShaderChannels = customListCanvasTemplate.additionalShaderChannels;
        canvas.overrideSorting = customListCanvasTemplate.overrideSorting;
        canvas.pixelPerfect = customListCanvasTemplate.pixelPerfect;
        canvas.referencePixelsPerUnit = customListCanvasTemplate.referencePixelsPerUnit;
        canvas.renderMode = customListCanvasTemplate.renderMode;
        canvas.scaleFactor = customListCanvasTemplate.scaleFactor;
        canvas.sortingLayerID = customListCanvasTemplate.sortingLayerID;
        canvas.sortingOrder = customListCanvasTemplate.sortingOrder;
        canvas.worldCamera = customListCanvasTemplate.worldCamera;

        gameObject.AddComponent<VRUIControls::VRGraphicRaycaster>().physicsRaycaster = Helpers::GetPhysicsRaycasterWithCache();
        gameObject.AddComponent<HMUI::Touchable>();
        gameObject.AddComponent<HMUI::EventSystemListener>();

        auto scrollView = gameObject.AddComponent<HMUI::ScrollView>();

        auto tableView = gameObject.AddComponent<BSML::TableView>();
        auto tableData = container.gameObject.AddComponent<CustomCellListTableData>();
        tableData.tableView = tableView;
        tableData.bsmlString = bsmlString;

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

    void CustomListTag::parse(const tinyxml2::XMLElement& elem) {
        BSMLTag::parse(elem);
        INFO("Getting BSML string contents");

        bsmlString = "";
        auto handle = tinyxml2::XMLConstHandle(elem).FirstChildElement();
        for (
            const tinyxml2::XMLElement* element = nullptr;
            (element = handle.ToElement()) != nullptr;
            handle = handle.NextSiblingElement()
        ) {
            tinyxml2::XMLPrinter printer(nullptr , true);
            element->Accept(&printer);
            bsmlString += std::string_view(printer.CStr(), printer.CStrSize());
        }

        INFO("Got BSML string: {}", bsmlString);
    }

    void CustomListTag::HandleChildren(UnityEngine::Transform parent, BSMLParserParams& parserParams, std::vector<ComponentTypeWithData*>& componentInfo) const {
        // intentionally not doing anything
    }
}
