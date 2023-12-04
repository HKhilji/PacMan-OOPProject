#include "enemy.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <memory>
#include <time.h>
#include <thread>

// void RedGhost::Ghost_Move(Grid& grid, Player& player, std::promise<void>&& prms){
// 	// red ghost uses a-star algo to chase
// 	RunAStarSearchAndMove(x, y, player.x, player.y, grid);
// 	prms.set_value();
// }


void BlueGhost::Ghost_Move(Grid& grid, Player& player, std::promise<void>&& prms){
	// blue ghost uses random moves
	RandomAlgo(grid);
	prms.set_value();
}

void BlueGhost::RandomAlgo(Grid& grid){
	// delta for all possible moves on the grid
	int delta[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	std::vector<std::vector<int>> moves;
	for(int i = 0; i < 4; i++){
		int x2 = x + delta[i][0];
		int y2 = y + delta[i][1];
		// for each neighbor cell..
		if(random_valid_cell(x2, y2, grid)){
			moves.push_back(std::vector<int>{x2, y2});
		}
	}
	if(moves.size() == 0){ 
		std::cerr << "Error: Blue Enemy has no moves left!\n";
		return;
	}
	// select one of the valid moves at random
	// the pseudo random generator is seeded at start of game 
	int random_index = rand() % (moves.size());
	// record prev position
	prev_x = x;
	prev_y = y;
	// move
	x = moves[random_index][0];
	y = moves[random_index][1];
}

bool BlueGhost::random_valid_cell(int x, int y, Grid& grid){
	// acquire grid mutex
	std::lock_guard<std::mutex> lck(grid.mtx);

	// check if out of grid
	if((x < 0) || (x > 18)){ return false; }
	if((y < 0) || (y > 22)){ return false; }

	// check for grid walls
	if(grid.at(x, y) == Grid::GridElement::kWall){ return false; }

	// prevent move to previous cell
	if((x == prev_x) && (y == prev_y)){ return false; }

	// prevent move into tunnel leading to portal
	if((x == 3) && (y == 10)){ return false; }
	if((x == 15) && (y == 10)){ return false; }

	// else it is valid cell to move
	return true;	
}