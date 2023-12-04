#include "SDL.h"
#include "controller.h"

void Controller::handleinputanddirection(bool& running, Player& player, Grid& grid){
    SDL_Event event; //this handles the events, reading and placing events on queue
    while (SDL_PollEvent(&event)) { //checking to pass info into the event.
    if (event.type == SDL.QUIT) { //sets running false if event is to quit
        running = false;
    }
    //this is for key detection, keydown is for detecting when key is pressed
    if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysm.sym) {
            

        }
    }
    }
}