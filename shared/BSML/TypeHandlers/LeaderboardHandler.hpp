#pragma once

#include "TypeHandler.hpp"
#include "GlobalNamespace/LeaderboardTableView.hpp"

namespace BSML {
    class LeaderboardHandler : public TypeHandler<GlobalNamespace::LeaderboardTableView*> {
        public:
            using Base = TypeHandler<GlobalNamespace::LeaderboardTableView*>;
            LeaderboardHandler() : Base() {}

            virtual Base::PropMap get_props() const override;
            virtual Base::SetterMap get_setters() const override;
    };
}