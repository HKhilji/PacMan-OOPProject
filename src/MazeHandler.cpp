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
}