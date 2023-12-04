#pragma once
#include "grid.h"
#include "player.h"
#include <vector>
#include <memory>
#include <future>

class ghost{
    public:
        ghost(int a, int b): x(a), y(b) {}
        int x, y; //positions
        virtual void Ghost_Move(Grid& grid, Player& player, std::promise<void>&& prms) = 0;
}

//random movement ghost
class BlueGhost{
    public:
        BlueGhost(int a, int b): ghost(a,b) {}
        void Ghost_Move(Grid& grid, Player& player, std::promise<void>&&prms) override;
    private:
        int prev_x = 0;
        int prev_y = 0;
        void RandomAlgo(Grid& grid);
        bool random_valid_cell(int x, int y, Grid& grid);
};

//searches for player
class RedGhost{
    public:
        RedGhost(int a, int b): ghost(a,b) {}
    private:
}