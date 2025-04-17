#include "../headers/mapLogic.h"
#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"

MapLogic::MapLogic(state& gs) : gs_state(gs), current_turnState(nullptr) {
	SetState(new AllayTurn(this));
} 

void MapLogic::SetState(TurnState* newTurnState)
{
	if (current_turnState)
		current_turnState->on_exit();
	current_turnState = newTurnState;
	current_turnState->on_enter();
}

void MapLogic::draw(state& g_state) const
{
	current_turnState->draw(gs_state);
}
void MapLogic::update() const
{
	current_turnState->update();
}
