#pragma once
#include "controller.h"
#include "GameRender.h"
#include "grid.h"
#include "player.h"

class Game{
    public:
        void GameLoop(controller& controller, GameRender& gamerenderer);
        int GetScore(){ return player.getScore(); }
        Grid grid;
        Player player;
        BlueGhost blue{10,10};
        RedGhost red{10,10};
        GreenGhost green{10,10};

    private:
        bool running = true;
        bool welcome = true;
        bool lost = false;
        bool win = false;
        void MovePlayer();
        void MoveEnemies();
        void CheckCollision(bool& running);
        void CheckWin(bool& running, Player& player);
        Uint32 frame_start;
        Uint32 frame_end;
        Uint32 frame_duration;
};