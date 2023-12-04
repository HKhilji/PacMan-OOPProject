#pragma once
#include "controller.h"
#include "GameRender.h"
#include "grid.h"
#include "player.h"

class Game{
    public:
        void GameLoop(Controller& controller, GameRender& renderer);
        int GetScore(){ return player.getScore(); }
        Grid grid;
        Player player;
        BlueEnemy blue(17,1);

    private:
        bool running = true;
        void MovePlayer();
        void MoveEnemies();
        void CheckCollision(bool& running);
        void CheckWin(bool& running, Player& player);
        Uint32 frame_start;
        Uint32 frame_end;
        Uint32 frame_duration;
};