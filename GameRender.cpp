#include "GameRender.h"
#include <iostream>

GameRender::GameRender(){
    sdl_window = SDL_CreateWindow("Pacman!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* iamge = SDL_LoadBMP("../res/gfx/pacman50x50spritesheet.bmp");
    tex = SDL_CreateTextureFromSurface(renderer, image);
}