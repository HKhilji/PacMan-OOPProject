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

        void RenderGameState(Grid& Grid, Player& player, BlueGhost& blue, RedGhost& red);
        void RenderWelcomeScreen();
        void RenderEndScreen();

        private:
            const std::size_t tile_width = 30;
            const std::size_t height = 23 * tile_width;
            const std::size_t width = 19 * tile_width;

            SDL_Window* sdl_window = nullptr;
            SDL_Renderer* renderer = nullptr;
            SDL_Texture* tex = nullptr;

            void DrawGrid(Grid& grid);
            void DrawPortals();
            void DrawPlayer(Player& player);
            void drawEnemy1(BlueGhost& blue);
            void drawEnemy2(RedGhost& red);
};