#include <headers/game.h>

class ManageTextures{
    public:
        ManageTextures();
        ~ManageTextures();
        static SDL_Renderer* renderer;
        static SDL_Texture* LoadTexture(const char* filename);
};