#include <headers/game.h>

int SDL_main(int argv, char* argc[]) {

    IMG_Init(IMG_INIT_PNG);

    int screenWidth = 672;
    int screenHeight = 888;

    Game game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    SDL_Texture* map = game.loadTexture("res/gfx/Map24.png");

    while (game._gameState != GameState::EXIT) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                game._gameState = GameState::EXIT;
                break;
        }

        game.run(map);
    }

    IMG_Quit();
    return 0;
}
