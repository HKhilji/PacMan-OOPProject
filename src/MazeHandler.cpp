#include "MazeHandler.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <headers/game.h>

std::vector<std::vector<char>> MazeGraph::graph;
std::vector<std::vector<short>> MazeGraph::food;
unsigned MazeGraph::x_o, y_o;
unsigned MazeGraph::cellSize;
unsigned MazeGraph::width;
unsigned MazeGraph::length;
int MazeGraph::food_count;

MazeGraph::MazeGraph(){
    cellSize = 20;
    width, length = 0;
    x_o, y_o = 0;
    food_count = 0;
}

MazeGraph::~MazeGraph(){}

void MazeGraph::ReadTextToGraph(){

    std::fstream fin;
    fin.open("src/Maze.txt");
    //Maybe if an error comes handle it, will add implementation later.

    std::string line, temp;
    while (fin >> temp){
        getline(fin, line);
        std::vector<char> temp;
        for (int i = 0; i < line.length(); i++){
            if(line[i] != ' ')
                temp.push_back(line[i]);
        }
        graph.push_back(temp);
    }

    //this is reading the text file line by line, and adding it to the graph vector./
    //now we have to do the same thing for the pellets./

    for (int i = 0; i < graph.size(); i++){
        std::vector<short> temp;
        for(int j = 0; j < graph[0].size();i++){
            if (graph[i][j] == '.' || graph[i][j] == ',' || (i > 8 && i < 20 && j > 6 && j < 21)){
                temp.push_back(0);
            }
            else if((!(i-23) || !(i-4)) && (!(j-1) || !(j-26))){
                food_count++;
                temp.push_back(2);
            }
            else{
                food_count++;
                temp.push_back(1);
            }
        }
        food.push_back(temp);
    }
    length = graph.size() * cellSize;
    width = graph[0].size() * cellSize;
}

void MazeGraph::PrintGraph(){ //prints the entire graph to console, used for debugging.

    for(auto g: graph){
        for (auto c: g){
            std::cout << std::endl;
        }
    }
}

void MazeGraph::RenderCells(int a, int b, bool complete){
    unsigned delx = x_o + b * cellSize;
    unsigned dely = y_o + a * cellSize;
    SDL_Rect Rect;

    if (graph[a][b] == '.'){
        if (complete){
            if (maze_complete_fps > 5){
                SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
            }
            else{
                SDL_SetRenderDrawColor(Game::renderer, 0, 128, 255, 255);
            }
            if (maze_complete_fps > 10)
                maze_complete_fps = 0;
        }
        else{
            SDL_SetRenderDrawColor(Game::renderer, 0, 128, 255, 255);
            maze_complete_fps = 0;
        }
    }

    else if (graph[i][j] == 'p'){
        SDL_SetRenderDrawColor(Game::renderer, 255, 192, 203, 255);
        Rect = {(int)(delx), (int)(dely  + cellSize / 8 * 3), (int)(cellSize/2), (int)(cellSize/4)};
        SDL_RenderFillRect(Game::renderer, &Rect);
        Rect = {(int)(delx+cellSize/2), (int)(dely + cellSize/8 * 3), (int)(cellSize/2), (int)(cellSize/4)};
        SDL_RenderFillRect(Game::renderer, &Rect);
        return;
    }

    if(i - 1 > -1 && graph[i-1][j] == '.'){
        //Draw a rect connecting that edge
        Rect = {(int)(delx + cellSize / 8 * 3), (int)(dely), (int)(cellSize/4), (int)(cellSize/2)};
        SDL_RenderFillRect(Game::renderer, &Rect);
    }
    if(j - 1 > -1 && graph[i][j-1] == '.'){
        Rect = {(int)(delx), (int)(dely  + cellSize / 8 * 3), (int)(cellSize/2), (int)(cellSize/4)};
        SDL_RenderFillRect(Game::renderer, &Rect);
    }
    if(i + 1 < (int)graph.size() && graph[i+1][j] == '.'){
        Rect = {(int)(delx + cellSize / 8 * 3), (int)(dely + cellSize/2), (int)(cellSize/4), (int)(cellSize/2)};
        SDL_RenderFillRect(Game::renderer, &Rect);
    }
    if(j + 1 < (int)graph[0].size() && graph[i][j+1] == '.'){
        Rect = {(int)(delx+cellSize/2), (int)(dely + cellSize/8 * 3), (int)(cellSize/2), (int)(cellSize/4)};
        SDL_RenderFillRect(Game::renderer, &Rect);
    }
}

void MazeGraph::RenderMaze(bool complete){

    cellSize = 24;
    x_o = 400 - graph[0].size()*cellSize/2;
    y_o = 400 - graph.size()*cellSize/2;
    SDL_Rect Rect;
    maze_complete_fps = complete ? maze_complete_fps + 1 : 0;
    for(unsigned i = 0; i < graph.size(); i++){
        for(unsigned j = 0; j < graph[0].size(); j++){
                
                RenderCellWall(i, j, complete); // calls the function to render the map wall.
                
                //then it generates all the food items in the game;

                unsigned delx = x_o + j * cellSize, dely = y_o + i * cellSize;
                bool is_food = true;
                switch(pellets[i][j]){
                    case 1:
                        Rect = {(int)(delx + cellSize/8 *3), (int)(dely + cellSize/8 * 3), (int)(cellSize/4), (int)(cellSize/4)};
                        SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
                        break;
                    case 2:
                        Rect = {(int)(delx + cellSize/4), (int)(dely + cellSize/4), (int)(cellSize/2), (int)(cellSize/2)};
                        SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
                        break;
                    default:
                        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
                        is_food = false;
                        break;
                }
                if(is_food){
                    SDL_RenderFillRect(Game::renderer, &Rect);
                    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
                }
        }
    }
}

void MazeGraph::MazeClear()
{
    while(graph.size()){
        graph.pop_back();
    }
    while(food.size()){
        food.pop_back();
    }
    food_count = 0;
}
