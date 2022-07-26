#pragma once

#include "UnityEngine/Transform.hpp"
#include "BSML/Tags/BSMLTag.hpp"

namespace BSML {
    
    /// @brief Intialize BSML for it's hooks 
    void Init();
    
    /// @brief parse a string containing a BSML doc 
    /// @return BSMLTag pointer to parsed hierarchy
    std::shared_ptr<BSMLTag> parse(std::string_view str);

    /// @brief parse a string containing a BSML doc 
    /// @param str the string to parse
    /// @param parent what to parent to
    /// @param host the host object, this would contain the various fields and properties your bsml expects to be able to access
    void parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host);
}