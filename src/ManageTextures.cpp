#include "ManageTextures.h"

ManageTextures::ManageTextures(){}
ManageTextures::~ManageTextures(){}

SDL_Texture* ManageTextures::LoadTexture(const char* filename){
    if (!IMG_Load(filename)){
        std::cout << "Can't load asset." << std::endl;
    }
    SDL_Surface* tempSurface =  IMG_Load(filename);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}