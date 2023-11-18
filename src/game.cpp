#include <headers/game.h>

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::run(SDL_Texture* map) {
    clear();
    render(map);
    display();
}

SDL_Texture* Game::loadTexture(const char* filePath) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, filePath);

    if (tex == NULL) {
        std::cout << "Image couldn't be loaded from path: " << filePath << std::endl;
    }

    return tex;
}

void Game::render(SDL_Texture* tex) {
    
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 672;
    src.h = 888;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 672;
    dst.h = 888;

    SDL_RenderCopy(renderer, tex, &src, &dst);
    SDL_RenderPresent(renderer);  // Add this line to update the screen

}

void Game::display() {
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_RenderClear(renderer);
}

void Game::cleanUp() {
    SDL_DestroyWindow(window);
}
