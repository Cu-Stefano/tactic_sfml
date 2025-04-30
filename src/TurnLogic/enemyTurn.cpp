#include "../headers/turnState.hpp"
#include "../headers/enemyTurn.h"  

#include "../headers/mapBuilder.h"
#include "../headers/MapLogic.h"  
#include "../headers/tile.h"
#include "../headers/unit.h"

class Turnstate;

EnemyTurn::EnemyTurn(MapLogic* map_logic) : TurnState(map_logic->gState), pathAlgorithm(nullptr)
{
	this->map_logic = map_logic;
}

void EnemyTurn::initialize_path_algorithm(Tile* unit)
{
	pathAlgorithm = new PathAlgorithm(unit, gState);
}

void EnemyTurn::HandleNoAllayToAttack(Tile* tile)
{
    tile->unitOn->has_moved();
	tile->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
	tile->unitOn->canMove = false;
}

void EnemyTurn::on_enter() {
	for (auto enemy_tile : enemy_tile_list)
	{
        if (!enemy_tile->unitOn->canMove) continue;

        initialize_path_algorithm(enemy_tile);

        auto allayToAttack = pathAlgorithm->attackList[0];

		if (allayToAttack == nullptr)
		{
			HandleNoAllayToAttack(enemy_tile);
			continue;
		}



		
	}

}  

void EnemyTurn::on_exit() {
     
}  

void EnemyTurn::update() {
  
}  

void EnemyTurn::draw(state& gState) {
    
}
