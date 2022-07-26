#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ModalKeyboardTagParser : private BSMLTagParser {
        private:
            ModalKeyboardTagParser();
            virtual BSMLTag* newTag() override;

            static ModalKeyboardTagParser modalKeyboardParser;
    };
}