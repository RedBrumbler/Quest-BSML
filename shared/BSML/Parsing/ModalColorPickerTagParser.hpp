#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ModalColorPickerTagParser : private BSMLTagParser {
        private:
            ModalColorPickerTagParser();
            virtual BSMLTag* newTag() override;

            static ModalColorPickerTagParser modalColorPickerTagParser;
    };
}