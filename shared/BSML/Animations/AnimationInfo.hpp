#pragma once

#include "../../_config.h"
#include <vector>
// this is just included because otherwise the SafePtr complains about conversion to unity object
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "UnityEngine/Object.hpp"

namespace BSML {
    class FrameInfo;
    class BSML_EXPORT AnimationInfo {
        public:
            ~AnimationInfo();
            bool isInitialized = false;
            int frameCount = 0;
            std::vector<FrameInfo*> frames;
    };

    class BSML_EXPORT FrameInfo {
        public:
            int width, height, bpp;
            SafePtr<Array<uint8_t>> colors;
            int delay;
            FrameInfo(int width, int height, int bpp = 4);
    };
}
