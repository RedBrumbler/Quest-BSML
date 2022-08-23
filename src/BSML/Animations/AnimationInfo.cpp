#include "BSML/Animations/AnimationInfo.hpp"

namespace BSML {
    AnimationInfo::~AnimationInfo() {
        for (auto f : frames) { if (f) delete f; }
    }

    FrameInfo::FrameInfo(int width, int height, int bpp) 
    : 
        width(width), 
        height(height), 
        colors(Array<uint8_t>::NewLength(width * height * bpp)), 
        delay(0) {}
}