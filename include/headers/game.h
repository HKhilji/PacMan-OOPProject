#pragma once
#include <iostream>
#include <sdl/SDL.h>
#include <sdl/sdl_image.h>

enum class GameState {PLAY, EXIT};

class Game {
    public:
        Game(const char* title, int x, int y, int w, int h, Uint32 flags);
        void run(SDL_Texture* tex);
        GameState _gameState;
        SDL_Texture* loadTexture (const char* filePath);
        void render(SDL_Texture* tex);
    private:
        void clear();
        void display();
        void cleanUp();
        SDL_Window* window;
        SDL_Renderer* renderer;
        
};