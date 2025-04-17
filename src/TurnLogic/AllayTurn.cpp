#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/mapLogic.h"  
#include "../headers/state.h"
#include "../headers/actionState.hpp"
#include "../headers/0_chooseTile.h"
#include "../headers/turnState.hpp"

class Turnstate;
class ActionState;
class ChooseTile;

AllayTurn::AllayTurn(MapLogic* map_logic) : TurnState(map_logic->gs_state) 
{
	this->map_logic = map_logic;
	CurrentActionState = nullptr;
}

void AllayTurn::on_enter()
{  
	SetActionState(new ChooseTile(gs_state, this));
}  

void AllayTurn::on_exit()
{
	for (auto tiles : gs_state.Map)
	{
		for (auto tile : tiles)
		{
			tile->onClick = nullptr;
		}
	}
}

void AllayTurn::SetActionState(ActionState* action)
{
	if (CurrentActionState != nullptr)
	{
		CurrentActionState->on_exit();
	}
	CurrentActionState = action;
	CurrentActionState->on_enter();
}

void AllayTurn::update()
{  
	CurrentActionState->update();
}  

void AllayTurn::draw(state& gs_state)
{  
	CurrentActionState->draw(gs_state);
}
