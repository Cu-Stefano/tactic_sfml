#pragma once
#include <utility>

class state;
class TurnState;

class ActionState
{
public:
	TurnState* turnState;
	state& gs_state;
	std::pair<int, int>  startinPosition;
	std::pair<int, int>  currentPosition;

	ActionState(state& gs_state, TurnState* turnState) : gs_state(gs_state), turnState(turnState) {}

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
};