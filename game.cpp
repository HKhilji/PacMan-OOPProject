#include "game.h"
#include "SDL.h"
#include <iostream>
#include <time.h>
#include <thread>
#include <future>
#define User_Reaction_ms 200

void Game::CheckWin(bool& running, Player& player){
    if (player.getScore() == 190){
        win = true;
        running = false;
    }
}

void Game::CheckCollision(bool& running){
    if ((player.x == blue.x) && (player.y == blue.y) || ((player.x == red.x) && (player.y == red.y)) || ((player.x == green.x) && (player.y = green.y))){
        lost = true;
        running = false;
    }
}

void Game::MoveEnemies(){ // picked up this logic for enemy movement from the internet.
                          // anticipates next position that the enemy has to move.
    std::promise<void> prms;
    std::future<void> ftr = prms.get_future();
    std::thread t(&BlueGhost::Ghost_Move, &blue, std::ref(grid), std::ref(player), std::move(prms));

    std::promise<void> prms2;
    std::future<void> ftr2 = prms2.get_future();
    std::thread t2(&RedGhost::Ghost_Move, &red, std::ref(grid), std::ref(player), std::move(prms2));

    std::promise<void> prms3;
    std::future<void> ftr3 = prms3.get_future();
    std::thread t3(&GreenGhost::Ghost_Move, &green, std::ref(grid), std::ref(player), std::move(prms3));

    // wait before checking for collisions
    ftr.wait();
    ftr2.wait();
    ftr3.wait();
    CheckCollision(running);

    t.join();
    t2.join();
    t3.join();
}

void Game::MovePlayer(){
    player.Move(grid);
    CheckWin(running, player);
    CheckCollision(running);
}

void Game::GameLoop(controller& controller, GameRender& gamerenderer){
    // creating the pseudo random number generator rand()
    srand(time(NULL));

    // the main game loop

    if (welcome){
        welcome = false;
        gamerenderer.RenderWelcomeScreen();
    }

    while (running){
        frame_start = SDL_GetTicks();

        //the function's name really gives it all away..
        controller.handleinputanddirection(running, player, grid);

        // Updates direction of player and dependent ghosts.
        MovePlayer();
        if (running){
            MoveEnemies();
        }
        if (lost){
            gamerenderer.RenderLoseScreen();
        }
        if (win){
            gamerenderer.RenderWinScreen();
        }
        
        // Render the changes on the screen
        gamerenderer.RenderGameState(grid, player, blue, red, green);

        //timing, changes come after the user inputs something
        frame_end = SDL_GetTicks();
        frame_duration = frame_end - frame_start;

        if (frame_duration < User_Reaction_ms){
            SDL_Delay(User_Reaction_ms - frame_duration);
        }    
        if (!running){
            SDL_Delay(1500);
        }
    }
}