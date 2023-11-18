#include <headers/game.h>

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::run(SDL_Texture* tex1, int select1, int x1, int y1, int w1, int h1,
               SDL_Texture* tex2, int select2, int x2, int y2, int w2, int h2,
               SDL_Texture* tex3, int select3, int x3, int y3, int w3, int h3,
               SDL_Texture* tex4, int select4, int x4, int y4, int w4, int h4) {
    clear();  // Clear the renderer before handling events and rendering
    HandleEvents();
    renderText("1up", 182, 10, 28);
    renderText(std::to_string(HighScore).c_str(), 182,40,28);
    render(tex1, x1, y1, w1, h1);
    render(tex2, x2, y2, w2, h2);
    render(tex3, x3, y3, w3, h3);
    render(tex4, x4, y4, w4, h4);
    display();
}

void Game::renderText(const char* text, int x, int y, int fontSize) {    
    TTF_Font* font = TTF_OpenFont("C:/Users/Dhaz/Documents/project/res/font/Retro.ttf", fontSize);
    if (font == nullptr) {
        std::cerr << "Error opening font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == nullptr) {
        // Handle surface creation error
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
}


void Game::render(SDL_Texture* tex, int x, int y, int w, int h){
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, tex, &src, &dst);
}

SDL_Texture* Game::loadTexture(const char* filePath) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, filePath);

    if (tex == NULL) {
        std::cout << "Image couldn't be loaded from path: " << filePath << std::endl;
    }

    return tex;
}

void Game::display() {
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_RenderClear(renderer);
}

void Game::cleanUp() {
    SDL_DestroyWindow(window);
    TTF_Quit();
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                std::cout << "Mouse Clicked at: (" << mouseX << ", " << mouseY << ")" << std::endl;
            }
            break;
        }
    }
}
