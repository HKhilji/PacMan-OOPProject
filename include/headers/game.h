#pragma once
#include <iostream>
#include <sdl/SDL.h>
#include <sdl/sdl_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>

enum class GameState {PLAY, EXIT};

class Game {
    public:
        Game(const char* title, int x, int y, int w, int h, Uint32 flags);
        void run(SDL_Texture* tex1, int select1, int x1, int y1, int w1, int h1,
               SDL_Texture* tex2, int select2, int x2, int y2, int w2, int h2,
               SDL_Texture* tex3, int select3, int x3, int y3, int w3, int h3,
               SDL_Texture* tex4, int select4, int x4, int y4, int w4, int h4);
        GameState _gameState;
        SDL_Texture* loadTexture (const char* filePath);
        void HandleEvents();
    private:
        void clear();
        void display();
        void cleanUp();
        void render(SDL_Texture* tex, int x, int y, int w, int h);
        void renderText(const char* text, int x, int y, int fontSize);
        SDL_Window* window;
        SDL_Renderer* renderer;
        int HighScore = 0000;
        
};
