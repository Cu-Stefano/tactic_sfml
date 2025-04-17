#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class state;
class TurnState;

class ActionState
{
public:
	TurnState* turnState;
	state& gs_state;
	sf::Vector2i startinPosition;
	sf::Vector2i currentPosition;

	ActionState(state& gs_state, TurnState* turnState) : gs_state(gs_state), turnState(turnState) {}

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;

	virtual void update() = 0;
	virtual void draw(state& gs_state) = 0;
};