#pragma once

#include "UnityEngine/Transform.hpp"
#include "BSML/Parsing/BSMLParser.hpp"
#include "BSML/MenuButtons/MenuButton.hpp"
#include "BSML/GameplaySetup/MenuType.hpp"

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

    namespace Register {
        /* Menu buttons are the buttons on the left in the main menu */
        /// @brief register a menu button for the left main menu
        /// @param text the text the button will display
        /// @param hoverHint the text that is displayed when the text is hovered
        /// @param onClick what to run when you click the button
        /// @return the created MenuButton*, or nullptr if it failed
        MenuButton* RegisterMenuButton(std::string_view text, std::string_view hoverHint = "", std::function<void(void)> onClick = nullptr);
    
        /// @brief register a menu button for the left main menu
        /// @param button the button to register
        /// @return true if successful, false if failed
        bool RegisterMenuButton(MenuButton* button);
    
        /// @brief unregister a menu button for the left main menu
        /// @param button the button to unregister
        /// @return true if successful, false if failed
        bool UnRegisterMenuButton(MenuButton* button);

        /* The settings menus are where the game settings are as well */
        /// @brief register a menu for the settings menu
        /// @param name the name displayed for your settings
        /// @param content_key the key for the BSML content to use for your settings
        /// @param host the host object, used as host for your BSML content
        /// @param enableExtraButtons whether to enable the extra ok / cancel buttons
        /// @return true if successful, false if failed
        bool RegisterSettingsMenu(std::string_view name, std::string_view content_key, Il2CppObject* host, bool enableExtraButtons = false);

        /// @brief remove a menu from the settings menu
        /// @param host the host object used when registering your menu
        /// @return true if successful, false if failed
        bool UnRegisterSettingsMenu(Il2CppObject* host);

        /* The gameplay tabs are where the song selection menu is */
        /// @brief register a tab for the gameplay setup menu
        /// @param name the name to display
        /// @param content_key the key for the BSML content for your settings
        /// @param host the host object, used as host for your BSML content
        /// @param menuType where your tab should be displayed. Default is All
        /// @return true if successful, false if failed
        bool RegisterGameplaySetupTab(std::string_view name, std::string_view content_key, Il2CppObject* host, MenuType menuType = MenuType::All);

        /// @brief remove a tab from the settings menu
        /// @param name the name of the tab to remove
        /// @return true if successful, false if failed
        bool UnRegisterGameplaySetupTab(std::string_view name);
    }
}