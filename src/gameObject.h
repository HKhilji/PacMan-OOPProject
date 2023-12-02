#include <iostream>
using namespace std;

#include "ManageTextures.h"

class GameObject{
    public:
        GameObject(const char* texturelist, int x, int y, int w, int l);
        ~GameObject();

        void Update(int x, int y);
        void Render();
        int getXpos();
        int getYpos();
        int getWidth();
        int getLength(); // getters to be used when dealing with collisions/rendering

    private:
        int xcord;
        int ycord;
        int width;
        int length;

        SDL_Texture* objectTex;
        SDL_Rect Rect;
        SDL_Renderer* renderer;
};