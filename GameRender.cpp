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

void GameRender::DrawGrid(Grid& grid){
    SDL_Rect Rect;
    for (int i = 0; i < 19; i++){
        for (int j = 0; j < 23; j++){
            //draw walls
            if ( grid.at(i,j) == Grid::GridElement::kWall){
                Rect.x = (i * tile_width) + ((tile_width * 3)/8);
                Rect.y = (j * tile_width) + ((tile_width * 3)/8);
                Rect.w = (tile_width/4);
                Rect.h = (tile_width/4);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &Rect);
                continue;
            }

            //draw empty cells, ie when there is no food
            if ( grid.at(i,j) == Grid::GridElement::kEmpty){
                Rect.x = i * tile_width;
                Rect.y = j * tile_width;
                Rect.w = tile_width;
                Rect.h = tile_width;

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &Rect);
                continue;
            }
        }
    }
}