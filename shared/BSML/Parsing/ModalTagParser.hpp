#pragma once

#include "BSML/Parsing/BSMLTagParser.hpp"

namespace BSML {
    class ModalTagParser : private BSMLTagParser {
        private:
            ModalTagParser();
            virtual BSMLTag* newTag() override;

            static ModalTagParser modalParser;
    };
}