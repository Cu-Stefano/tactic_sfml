#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/MapLogic.h"  
#include "../headers/state.hpp"
#include "../headers/actionState.hpp"
#include "../headers/0_chooseTile.h"
#include "../headers/tile.h"
#include "../headers/unit.h"

class Turnstate;
class ActionState;
class ChooseTile;

AllayTurn::AllayTurn(MapLogic* map_logic) : TurnState(map_logic->gsState) 
{
	this->map_logic = map_logic;
	CurrentActionState = nullptr;
}

void AllayTurn::on_enter()
{  
	SetActionState(new ChooseTile(gsState, this));
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
	bool allAlliesCannotMove = std::all_of(allay_list.begin(), allay_list.end(), [](Unit* unit) {
		return !unit->canMove;
		});

	if (allAlliesCannotMove && !Unit::IsAnyUnitMoving) {
		gsState.MapLogic.set_state(new EnemyTurn(&gsState.MapLogic));
	}
}  

void AllayTurn::draw(state& gsState)
{  
	CurrentActionState->draw(gsState);
}
