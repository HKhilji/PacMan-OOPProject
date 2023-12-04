#include "enemy.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <memory>
#include <time.h>
#include <thread>

void RedEnemy::Ghost_Move(Grid& grid, Player& player, std::promise<void>&& prms){
	// red ghost uses a-star algo to chase
	RunAStarSearchAndMove(x, y, player.x, player.y, grid);
	prms.set_value();
}
