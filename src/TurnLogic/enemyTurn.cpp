#include "../headers/turnState.hpp"
#include "../headers/enemyTurn.h"  
#include "../headers/MapLogic.h"  

class Turnstate;

EnemyTurn::EnemyTurn(MapLogic* map_logic) : TurnState(map_logic->gsState)
{
	this->map_logic = map_logic;
}

void EnemyTurn::on_enter() {
   
}  

void EnemyTurn::on_exit() {
     
}  

void EnemyTurn::update() {
  
}  

void EnemyTurn::draw(state& gState) {
    
}
