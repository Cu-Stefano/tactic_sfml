#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/MapLogic.h"  
#include "../headers/state.hpp"
#include "../headers/actionState.hpp"
#include "../headers/0_chooseTile.h"
#include "../headers/tile.h"
#include "../headers/unit.h"

using namespace sf;

class Turnstate;
class ActionState;
class ChooseTile;

AllayTurn::AllayTurn(MapLogic* map_logic) : TurnState(map_logic->gState) 
{
	this->map_logic = map_logic;
	CurrentActionState = nullptr;
}

void AllayTurn::on_enter()
{  
	SetActionState(new ChooseTile(gState, this));
}  

void AllayTurn::on_exit()
{
	for (auto unit : allay_list)
	{
		unit->canMove = true;
		unit->an_sprite.sprite->setColor(Color::White);
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

void AllayTurn::draw(state& gState)
{  
	CurrentActionState->draw(gState);
}
