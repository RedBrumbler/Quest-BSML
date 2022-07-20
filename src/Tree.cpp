#include "Tree.hpp"

namespace BSML {
    Tree Tree::parse(std::string_view str) {
        return Tree(str);
    }

    Tree::Tree(std::string_view str) {
        doc.Parse(str.data());
    }
}