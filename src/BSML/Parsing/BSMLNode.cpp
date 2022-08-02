#include "BSML/Parsing/BSMLNode.hpp"
#include "logging.hpp"

namespace BSML {
    BSMLNode::BSMLNode() : is_valid(false), children({}) {}
    BSMLNode::~BSMLNode() {
        for (auto child : children) {
            delete child;
        }
    }
    bool BSMLNode::valid() const {
        return is_valid;
    }

    void BSMLNode::AddChild(BSMLNode* child) {
        child->root = root;
        child->parent = this;
        children.emplace_back(child);
    }

    void BSMLNode::parse(const tinyxml2::XMLElement& elem) {
        INFO("Parsing Node: {}", elem.Name());
        is_valid = true;

        for (const tinyxml2::XMLAttribute* a = elem.FirstAttribute(); a; a = a->Next()) {
            attributes[a->Name()] = a->Value();
        }
    }

}