#pragma once
#include "grid.h"
#include "player.h"
#include <vector>
#include <memory>
#include <future>

class ghost{
    public:
        ghost(int a, int b): x(a), y(b) {}
        int x, y;
}

//random movement ghost
class BlueGhost{
    public:
        BlueGhost(int a, int b): ghost(a,b) {}
    private:
}

//searches for player
class RedGhost{
    public:
        RedGhost(int a, int b): ghost(a,b) {}
    private:
}