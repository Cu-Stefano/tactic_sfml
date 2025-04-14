#include "../headers/mapLogic.h"
#include "../headers/allayTurn.h"

MapLogic::MapLogic(state& gs) : gs_state(gs), current_turnState(nullptr) {
	SetState(new AllayTurn(this));
} 

void MapLogic::SetState(TurnState* newTurnState)
{
	current_turnState = newTurnState;
	current_turnState->on_enter();
}

void MapLogic::draw() const
{
	current_turnState->draw();
}
void MapLogic::update() const
{
	current_turnState->update();
}
