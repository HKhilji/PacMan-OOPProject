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

void Game::MoveEnemies(){
    std::promise<void> prms;
    std::future<void> ftr = prms.get_future();
    std::thread t(&BlueGhost::Ghost_Move, &blue, std::ref(grid), std::ref(player), std::move(prms));

    // wait before checking for collisions
    ftr.wait();
    CheckCollision(running);

    t.join();
}

void Game::MovePlayer(){
    player.Move(grid);
    CheckWin(running, player);
    CheckCollision(running);
}