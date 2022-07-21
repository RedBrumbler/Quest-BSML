#include "BSML.hpp"

extern "C" void load();

namespace BSML {
    void Init() {
        load();
    }
}