#include "GameRender.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

GameRender::GameRender(){
    sdl_window = SDL_CreateWindow("Pacman!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* image = SDL_LoadBMP("C:/Users/DELL/Documents/GitHub/PacMan-OOPProject/res/gfx/pacman50x50spritesheet.bmp");
    tex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = nullptr;
}

GameRender::~GameRender(){
    SDL_DestroyTexture(tex);
    tex = nullptr;

    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_Quit();
}

void GameRender::DrawPortals(){
    SDL_Rect Rect;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    Rect.x = 0 * tile_width;
    Rect.y = 10 * tile_width;
    Rect.w = tile_width;
    Rect.h = tile_width;
    SDL_RenderFillRect(renderer, &Rect);

    Rect.x = 18 * tile_width;
    Rect.y = 10 * tile_width;
    Rect.w = tile_width;
    Rect.h = tile_width;
    SDL_RenderFillRect(renderer, &Rect);
}

void GameRender::RenderWelcomeScreen(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
    SDL_RenderClear(renderer);

    // Load image
    SDL_Surface* imageSurface = IMG_Load("C:/Users/DELL/Documents/GitHub/PacMan-OOPProject/res/gfx/pakupaku.png");
    if (!imageSurface) {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        // Handle error accordingly
    }

    // Create texture from image surface
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!imageTexture) {
        std::cout << "Failed to create texture from image: " << SDL_GetError() << std::endl;
        // Handle error accordingly
    }

    TTF_Init();

    SDL_Color textColor = {255, 255, 255, 255};

    TTF_Font* font = TTF_OpenFont("C:/Users/DELL/Documents/GitHub/PacMan-OOPProject/res/font/retro.ttf", 20);
    if (!font) {
        std::cout << "Failure to load font" << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, "Welcome to Pacman", textColor);
    if (!surface) {
        std::cout << "Failure to create surface" << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex) {
        std::cout << "Failure to create texture" << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    int textWidth = surface->w;
    int textHeight = surface->h;
    int x = ((width - textWidth) / 2);
    int y = (((height - textHeight) / 2) + 40);

    SDL_Surface* surface2 = TTF_RenderText_Blended(font, "Press the 'Enter' key to play.", textColor);
    if (!surface2) {
        std::cout << "Failure to create surface" << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(renderer, surface2);
    if (!tex) {
        std::cout << "Failure to create texture" << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    int textWidth2 = surface2->w;
    int textHeight2 = surface2->h;
    int x2 = (width - textWidth2) / 2;
    int y2 = ((height - textHeight2) / 2) + 80;

    SDL_Rect destinationRect = {x, y, textWidth, textHeight};
    SDL_Rect destinationRect2 = {x2, y2, textWidth2, textHeight2};
    SDL_Rect imageRect = {75, 40, 426, 240}; 

    SDL_RenderCopy(renderer, tex, nullptr, &destinationRect);
    SDL_RenderCopy(renderer,tex2, nullptr, &destinationRect2);
    SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);
    SDL_RenderPresent(renderer);

    bool enterPressed = false;
    SDL_Event event;

    // Wait for Enter key press
    while (!enterPressed) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // Handle window close event
                enterPressed = true;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    // Enter key pressed
                    enterPressed = true;
                    break;
                }
            }
        }
        SDL_Delay(10); // Small delay to avoid high CPU usage
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(imageSurface);
    TTF_CloseFont(font);

    // Clear the renderer after Enter is pressed
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    TTF_Quit();
}



void GameRender::RenderGameState(Grid& Grid, Player& player, BlueGhost& blue, RedGhost& red){
    // create a blank screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // draw the grid;
    DrawGrid(Grid);
    // draw portals
    DrawPortals();
    // draw player
    DrawPlayer(player);
    // draw enemy
    drawEnemy1(blue);
    drawEnemy2(red);
    //finally render everything
    SDL_RenderPresent(renderer);
}

void GameRender::DrawGrid(Grid& grid){
    SDL_Rect Rect;
    for (int i = 0; i < 19; i++){
        for (int j = 0; j < 23; j++){
            
            // draw grid's wall cells
			if( grid.at(i, j) == Grid::GridElement::kWall){
				Rect.x = i * tile_width; 
				Rect.y = j * tile_width;
				Rect.w = tile_width; 
				Rect.h = tile_width;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
				SDL_RenderFillRect(renderer, &Rect);
				continue;
			}
            
            //draw food cells
            if ( grid.at(i,j) == Grid::GridElement::kFood){
                Rect.x = (i * tile_width) + ((tile_width * 3)/8);
                Rect.y = (j * tile_width) + ((tile_width * 3)/8);
                Rect.w = ((tile_width*1)/4);
                Rect.h = ((tile_width*1)/4);

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

void GameRender::DrawPlayer(Player& player){
    SDL_Rect Rect1; // source rect
    SDL_Rect Rect2; // destination rect

    player.frame = (player.frame + 1) % 2;
    Rect1.x = player.frame * 50;
    Rect1.y = player.direction * 50;
    Rect1.w = 50;
    Rect1.h = 50;

    Rect2.x = player.x * tile_width;
    Rect2.y = player.y * tile_width;
    Rect2.w = tile_width;
    Rect2.h = tile_width;
    SDL_RenderCopy(renderer, tex, &Rect1, &Rect2);
}

void GameRender::drawEnemy1(BlueGhost& blue){
    SDL_Rect Rect1; // source rect
    SDL_Rect Rect2; // destination rect

    Rect1.x = 3 * 50;
	Rect1.y = 0 * 50;
	Rect1.w = 50; 
	Rect1.h = 50;
	Rect2.x = blue.x * tile_width; 
	Rect2.y = blue.y * tile_width; 
	Rect2.w = tile_width; 
	Rect2.h = tile_width;
	SDL_RenderCopy(renderer, tex, &Rect1, &Rect2);

}

void GameRender::drawEnemy2(RedGhost& red){
    SDL_Rect Rect1; // source rect
    SDL_Rect Rect2; // destination rect

    red.frame = (red.frame + 1) % 16;
	Rect1.x = 2 * 50;
    Rect1.y = (red.frame/4) * 50;
	Rect1.w = 50; 
	Rect1.h = 50;
	Rect2.x = red.x * tile_width; 
	Rect2.y = red.y * tile_width; 
	Rect2.w = tile_width; 
	Rect2.h = tile_width;
	SDL_RenderCopy(renderer, tex, &Rect1, &Rect2);

}