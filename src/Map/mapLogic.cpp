#include "../headers/MapLogic.h"
#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"

MapLogic::MapLogic(state& gs) : gsState(gs), current_turnState(nullptr) {
	set_state(new AllayTurn(this));
} 

void MapLogic::set_state(TurnState* newTurnState)
{
	if (current_turnState)
		current_turnState->on_exit();
	current_turnState = newTurnState;
	current_turnState->on_enter();
}

void MapLogic::draw(state& gState) const
{
	current_turnState->draw(gsState);
}
void MapLogic::update() const
{
	current_turnState->update();
}
