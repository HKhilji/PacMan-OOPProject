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
};

//random movement ghost
class BlueGhost : public ghost{
    public:
        BlueGhost(int a, int b) : ghost(a,b) {}
        void Ghost_Move(Grid& grid, Player& player, std::promise<void>&&prms) override;
    private:
        int prev_x = 0;
        int prev_y = 0;
        void RandomAlgo(Grid& grid);
        bool random_valid_cell(int x, int y, Grid& grid);
};

//searches for player
// class RedGhost{
//     public:
//         RedGhost(int a, int b): ghost(a,b) {}
//         void Ghost_Move(Grid& grid, Player& player, std::promise<void>&&prms) override;
//         //node for a star search algorithm
//         struct Node {
//             int x;
//             int y;
//             int g;
//             int h;
//             std::shared_ptr<Node> parent = nullptr;
//         };
//         std::vector<std::vector<int>> ai_path;
//         int frame = 0;
//     private:
//         void RunRedSearch(int start_x, int start_y, int goal_x, int goal_y, Grid& grid);
//         int Heuristic(int x1, int y1, int x2, int y2);
//         bool AStar_checkCell(int x, int y, Grid& grid, int(&visited_Nodes)[19][23]);
// };