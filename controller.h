#pragma once
#include "player.h"
#include "grid.h"

class controller {
    public:
        void handleinputanddirection(bool& moving, Player& player, Grid& grid);
};