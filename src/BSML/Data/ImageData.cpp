#include "BSML/Data/ImageData.hpp"
#include "internal_macros.hpp"
#include "logging.hpp"

namespace BSML {
    ImageData::ImageData(const tinyxml2::XMLElement& elem) {
        // TODO: implement
    }
    
    void ImageData::Apply(UnityEngine::UI::Image* image) const {
        if (!image) {
            ERROR("nullptr passed to ImageData::Apply");
            return;
        }
        // TODO: implement
    }
}