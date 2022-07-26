#include "BSML.hpp"
#include "BSML/Parsing/BSMLDocParser.hpp"

extern "C" void load();

namespace BSML {
    void Init() {
        load();
    }

    std::shared_ptr<BSMLTag> parse(std::string_view str) {
        Init();
        return BSMLDocParser::parse(str);
    }
    
    void parse_and_construct(std::string_view str, UnityEngine::Transform* parent, Il2CppObject* host) {
        Init();
        auto tag = parse(str);
        tag->Construct(parent, host);
    }
}