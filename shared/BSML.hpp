#pragma once

#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLParser.hpp"
#include "BSML/MenuButtons/MenuButton.hpp"

namespace BSML {
    
    /// @brief Intialize BSML for it's hooks 
    void Init();
    
    /// @brief parse a string containing a BSML doc 
    /// @return BSMLNode pointer to parsed hierarchy
    std::shared_ptr<BSMLParser> parse(std::string_view str);

    /// @brief parse a string containing a BSML doc 
    /// @param str the string to parse
    /// @param parent what to parent to
    /// @param host the host object, this would contain the various fields and properties your bsml expects to be able to access
    /// @return parserparams result
    std::shared_ptr<BSMLParser> parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host);

    /// @brief register a menu button for the left main menu
    /// @param button the button to register
    /// @return true if successful, false if failed
    bool RegisterMenuButton(MenuButton* button);

    /// @brief unregister a menu button for the left main menu
    /// @param button the button to unregister
    /// @return true if successful, false if failed
    bool UnRegisterMenuButton(MenuButton* button);
}