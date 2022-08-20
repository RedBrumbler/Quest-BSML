#pragma once

namespace BSML {
    enum class MenuType {
        None = 0,
        Solo = 1,
        Online = 2,
        Campaign = 4,
        Custom = 8,
        All = Solo | Online | Campaign | Custom
    };
    bool operator!(const MenuType& type);
    MenuType operator |(const MenuType& lhs, const MenuType& rhs); 
    MenuType& operator |=(MenuType& lhs, const MenuType& rhs); 
    MenuType operator &(const MenuType& lhs, const MenuType& rhs); 
    MenuType& operator &=(MenuType& lhs, const MenuType& rhs); 
}