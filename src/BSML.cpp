#include "BSML.hpp"

extern "C" void load();

namespace BSML {
    void Init() {
        load();
    }

    Tree parse(std::string_view str) {
        return Tree::parse(str);
    }
}