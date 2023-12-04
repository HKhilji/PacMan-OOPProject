//Oh God, this is where we will find out.

#include <iostream>
#include "grid.h"
#include "GameRender.h"
#include "controller.h"
#include "game.h"

#ifdef _WIN32
#include <windows.h>

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
#else
int main() {
#endif
    GameRender renderer;
    controller controller;
    Game game;
    game.GameLoop(controller, renderer);
    std::cout << "--Game terminated successfully--\n";
    return 0;
}