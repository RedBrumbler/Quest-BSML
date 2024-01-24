#include "BSML-Lite/Creation/Lists.hpp"
#include "BSML-Lite/Creation/Layout.hpp"
#include "BSML-Lite/Creation/Buttons.hpp"
#include "BSML-Lite/Creation/Image.hpp"
#include "assets.hpp"

#include "Helpers/getters.hpp"
#include "Helpers/utilities.hpp"
#define protected public
#include "BSML/Tags/ListTag.hpp"
#undef protected
#include "HMUI/ScrollView.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace BSML::Lite {
    BSML::CustomListTableData* CreateList(const TransformWrapper& parent, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, std::function<void(int)> onCellWithIdxClicked) {
        auto go = BSML::ListTag{}.CreateObject(parent);
        auto list = go->GetComponent<BSML::CustomListTableData*>();
        list->tableView->scrollView->_platformHelper = BSML::Helpers::GetIVRPlatformHelper();

        auto rect = go->transform.cast<UnityEngine::RectTransform>();
        rect->set_anchoredPosition(anchoredPosition);
        rect->set_sizeDelta(sizeDelta);

        auto layoutElement = go->GetComponent<UnityEngine::UI::LayoutElement*>();
        if (layoutElement) {
            layoutElement->set_preferredHeight(sizeDelta.y);
            layoutElement->set_flexibleHeight(sizeDelta.y);
            layoutElement->set_minHeight(sizeDelta.y);
            layoutElement->set_preferredWidth(sizeDelta.x);
            layoutElement->set_flexibleWidth(sizeDelta.x);
            layoutElement->set_minWidth(sizeDelta.x);
        }

        if (onCellWithIdxClicked) {
            list->tableView->add_didSelectCellWithIdxEvent(
                custom_types::MakeDelegate<System::Action_2<UnityW<HMUI::TableView>, int>*>(
                    std::function<void(HMUI::TableView*, int)>(
                        [onCellWithIdxClicked](HMUI::TableView* _, int idx){ onCellWithIdxClicked(idx); }
                    )
                )
            );
        }

        return list;
    }

    UnityEngine::Sprite* get_carat_down() {
        static SafePtrUnity<UnityEngine::Sprite> carat_down;
        if (!carat_down) {
            auto sprite = BSML::Utilities::LoadSpriteRaw(Assets::carat_down_png);
            UnityEngine::Object::DontDestroyOnLoad(sprite);
            carat_down = sprite;
        }
        return carat_down.ptr();
    }

    UnityEngine::Sprite* get_carat_up() {
        static SafePtrUnity<UnityEngine::Sprite> carat_up;
        if (!carat_up) {
            auto sprite = BSML::Utilities::LoadSpriteRaw(Assets::carat_up_png);
            UnityEngine::Object::DontDestroyOnLoad(sprite);
            carat_up = sprite;
        }
        return carat_up.ptr();
    }

    BSML::CustomListTableData* CreateScrollableList(const TransformWrapper& parent, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, std::function<void(int)> onCellWithIdxClicked) {
        auto vertical = CreateVerticalLayoutGroup(parent);
        auto rect = vertical->rectTransform;
        rect->set_anchoredPosition(anchoredPosition);
        rect->set_sizeDelta(sizeDelta);

        auto list = CreateList(rect.unsafePtr(), {}, {sizeDelta.x, sizeDelta.y - 16}, onCellWithIdxClicked);
        auto pageUp = CreateClickableImage(vertical, get_carat_up(), [scrollView = list->tableView->scrollView.unsafePtr()](){
            if (scrollView && scrollView->m_CachedPtr) scrollView->PageUpButtonPressed();
        });
        pageUp->highlightColor = {1.0, 1.0, 1.0, 0.5};
        pageUp->get_transform()->SetAsFirstSibling();
        auto pageDown = CreateClickableImage(vertical, get_carat_down(), [scrollView = list->tableView->scrollView.unsafePtr()](){
            if (scrollView && scrollView->m_CachedPtr) scrollView->PageDownButtonPressed();
        });
        pageDown->highlightColor = {1.0, 1.0, 1.0, 0.5};

        pageUp->get_rectTransform()->set_sizeDelta({8.0f, 8.0f});
        pageDown->get_rectTransform()->set_sizeDelta({8.0f, 8.0f});

        return list;
    }

    HMUI::TableView::IDataSource* CreateCustomSourceList(System::Type* type, const TransformWrapper& parent, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, std::function<void(int)> onCellWithIdxClicked) {
        auto list = CreateList(parent, anchoredPosition, sizeDelta, onCellWithIdxClicked);

        auto tableView = list->tableView;
        auto go = list->get_gameObject();
        UnityEngine::Object::DestroyImmediate(list);
        auto dataSource = go->AddComponent(type);
        auto iDataSource = reinterpret_cast<HMUI::TableView::IDataSource*>(dataSource.unsafePtr());

        auto finfo = il2cpp_functions::class_get_field_from_name(dataSource->klass, "tableView");
        if (finfo) // there is a field named tableView
            il2cpp_utils::SetFieldValue(dataSource, finfo, tableView);
        tableView->SetDataSource(iDataSource, false);

        return iDataSource;
    }

    HMUI::TableView::IDataSource* CreateScrollableCustomSourceList(System::Type* type, const TransformWrapper& parent, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, std::function<void(int)> onCellWithIdxClicked) {
        auto list = CreateScrollableList(parent, anchoredPosition, sizeDelta, onCellWithIdxClicked);

        auto tableView = list->tableView;
        auto go = list->get_gameObject();
        UnityEngine::Object::DestroyImmediate(list);
        auto dataSource = go->AddComponent(type);
        auto iDataSource = reinterpret_cast<HMUI::TableView::IDataSource*>(dataSource.unsafePtr());
        auto finfo = il2cpp_functions::class_get_field_from_name(dataSource->klass, "tableView");
        if (finfo) // there is a field named tableView
            il2cpp_utils::SetFieldValue(dataSource, finfo, tableView);
        tableView->SetDataSource(iDataSource, false);

        return iDataSource;
    }

}
