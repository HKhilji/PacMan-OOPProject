#include "SDL.h"
#include "controller.h"

void controller::handleinputanddirection(bool& moving, Player& player, Grid& grid){
    SDL_Event event; //this handles the events, reading and placing events on queue
    while (SDL_PollEvent(&event)) { //checking to pass info into the event.
        if (event.type == SDL_QUIT) { //sets moving false if event is to quit
            moving = false;
        }
        //this is for key detection, keydown is for detecting when key is pressed
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP: //this if condition is just to check if collisison with wall. uses grid.cpp
                    player.direction = (grid.at(player.x, player.y-1) == Grid::GridElement::kWall)? player.direction : Player::Direction::kUp;
                    break;
                case SDLK_DOWN: 
					player.direction = (grid.at(player.x, player.y+1) == Grid::GridElement::kWall)? player.direction : Player::Direction::kDown; 
					break;
                case SDLK_LEFT: 
					player.direction = (grid.at(player.x-1, player.y) == Grid::GridElement::kWall)? player.direction : Player::Direction::kLeft; 
					break;
                case SDLK_RIGHT: 
					player.direction = (grid.at(player.x+1, player.y) == Grid::GridElement::kWall)? player.direction : Player::Direction::kRight; 
					break;

            }
        }
    }
}