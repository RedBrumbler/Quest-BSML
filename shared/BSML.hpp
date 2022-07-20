#pragma once

#include "Tree.hpp"

namespace BSML {
    void Init();

    Tree parse(std::string_view str);
}