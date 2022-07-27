#include "BSML/Data/PageButtonData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"
#include <map>

#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Quaternion.hpp"

std::map<std::string, BSML::PageButtonData::PageButtonDirection> stringToPageButtonDirectionMap {
    {"Up", BSML::PageButtonData::PageButtonDirection::Up},
    {"Down", BSML::PageButtonData::PageButtonDirection::Down},
    {"Left", BSML::PageButtonData::PageButtonDirection::Left},
    {"Right", BSML::PageButtonData::PageButtonDirection::Right}
};

BSML::PageButtonData::PageButtonDirection stringToPageButtonDirection(std::string str) {
    auto itr = stringToPageButtonDirectionMap.find(str);
    if (itr == stringToPageButtonDirectionMap.end()) return BSML::PageButtonData::PageButtonDirection::Up;
    return itr->second;
}


namespace BSML {
    PageButtonData::PageButtonData(const tinyxml2::XMLElement& elem) {
        std::string temp;
        GET_BSML_STRING("direction", temp);
        GET_BSML_STRING("dir", temp);

        pageButtonDirection = stringToPageButtonDirection(temp);
    }
    
    void PageButtonData::Apply(BSML::PageButton* pageButton) const {
        if (!pageButton) {
            ERROR("nullptr passed to PageButtonData::Apply");
            return;
        }

        bool isHorizontal = false;
        int angle = 0;

        auto buttonTransform = reinterpret_cast<UnityEngine::RectTransform*>(pageButton->get_transform()->Find("Icon"));
        buttonTransform->set_anchoredPosition({0, 0});
        auto layoutElement = pageButton->GetComponent<UnityEngine::UI::LayoutElement*>();
        switch(pageButtonDirection) {
            case PageButtonDirection::Up:
                isHorizontal = true;
                angle = -180;
                break;
            case PageButtonDirection::Down:
                isHorizontal = true;
                angle = 0;
                break;
            case PageButtonDirection::Left:
                isHorizontal = false;
                angle = -90;
                break;
            case PageButtonDirection::Right:
                isHorizontal = false;
                angle = 90;
                break;
        }
        buttonTransform->set_localRotation(UnityEngine::Quaternion::Euler(0, 0, angle));
        if (layoutElement->get_preferredHeight() == -1) {
            layoutElement->set_preferredHeight(isHorizontal ? 6 : 40);
        }

        if (layoutElement->get_preferredWidth() == -1) {
            layoutElement->set_preferredWidth(isHorizontal ? 40 : 6);
        }
    }
}