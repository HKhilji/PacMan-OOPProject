#include <headers/game.h>

int SDL_main(int argv, char* argc[]) {

    int screenWidth = 766;
    int screenHeight = 1000;

    Game game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    SDL_Texture* map = game.loadTexture("res/gfx/map.png");
    SDL_Texture* lives = game.loadTexture("res/gfx/Lives32.png");

    while (game._gameState != GameState::EXIT) {
        game.run(map, 1, 0, 90, screenWidth, 849, lives, 0, 23, 962, 32, 32, lives, 0, 60, 962, 32, 32, lives, 0, 97, 962, 32, 32);
    }

    return 0;
}
