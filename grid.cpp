#include "grid.h"
#include <iostream>
#include <fstream>

Grid::Grid()
{
  loadGamerGrid();
}

void Grid::LoadGamerGrid()
{
  int i = 0;
  std::ifstream ifs("../data/grid.txt");
  if(!ifs)
  { 
    std::cerr << "Failed to open file <../data/grid.txt>\n";
    return;
  };
  std::string line;
while(std::getline(ifs,line))
  {
    for(int j = 0; j < 19; j++)
    {
      grid[i][j] = line[j] - '0';
    }
  i++;
  }
}

void Grid::PrintFameGrid()
{
  for(int i = 0; i < 23; i++)
  {
    for(int j = 0; j < 29; j++)
    {
      std::cout << grid[i][j];
    }
  }
  return;
}

int Grid::at(int x, int y)
{
  return grid[x][y];
}

void Grid::set(int x, int y, int val)
{
  grid[y][x] = val;
}
  
