//Oh God, this is where we will find out.

#include <iostream>
#include "grid.h"
#include "GameRender.h"
#include "controller.h"
#include "game.h"

int main(){
    GameRender renderer;
    controller controller;
    Game game;
    game.GameLoop(controller, renderer);
    std::cout << "--Game terminated successfully--\n";
    return 0;
}
