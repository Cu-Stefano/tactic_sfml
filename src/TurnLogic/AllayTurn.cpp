#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/mapLogic.h"  

AllayTurn::AllayTurn(MapLogic* map_logic) : TurnState(map_logic->gs_state) 
{
	this->map_logic = map_logic;
}

void AllayTurn::on_enter() {  
   // Implementation for entering AllayTurn  
}  

void AllayTurn::on_exit() {  
   // Implementation for exiting AllayTurn  
}  

void AllayTurn::update() {  
   // Implementation for updating AllayTurn  
}  

void AllayTurn::draw() {  
   // Implementation for drawing AllayTurn  
}
