#pragma once

#include "SDL.h"
#include "grid.h"
#include "player.h"
#include "enemy.h"

class GameRender{
    public:
        GameRender();
        ~GameRender();

        //making the remaining possible constructors just to be safe.

        void RenderGameState(Grid& Grid, Player& player, BlueEnemy& blue);

        private:
            const std::size_t tile_width = 30;
            const std::size_t height = 23 * tile_width;
            const std::size_t width = 23 * tile_width;

            SDL_Window* sdl_window = nullptr;
            SDL_Renderer* renderer = nullptr;
            SDL_Texture* tex = nullptr;

            void DrawGridG(Grid& grid);
            void DrawPlayer(Player& player);
            void drawEnemy(BlueEnemy& blue);
};