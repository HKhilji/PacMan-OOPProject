#include "game.h"
#include "SDL.h"
#include <iostream>
#include <time.h>
#include <thread>
#include <future>
#define User_Reaction_ms 200

void Game::CheckWin(bool& running, Player& player){
    if (player.getScore() == 190){
        std::cout << "You Win!" << std::endl;
        running = false;
    }
}

void Game::CheckCollision(bool& running){
    if ((player.x == blue.x) && (player.y == blue.y)){
        running = false;
        std::cout << "You Lost!" << std::endl;
    }
}
