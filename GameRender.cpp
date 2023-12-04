#include "GameRender.h"
#include <iostream>

GameRender::GameRender(){
    sdl_window = SDL_CreateWindow("Pacman!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* image = SDL_LoadBMP("../res/gfx/pacman50x50spritesheet.bmp");
    tex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = nullptr;
}

GameRender::~GameRender(){
    SDL_DestroyTexture(tex);
    tex = nullptr;

    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;
}

void GameRender::RenderGameState(Grid& grid, Player& player, BlueEnemy& blue){
    // create a blank screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // draw the grid;
    DrawGrid(grid);
    // draw player
    DrawPlayer(player);
    // draw enemy
    drawEnemy(blue);
    //finally render everything
    SDL_RenderPresent(renderer);
}

