#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class state;
class TurnState;

class ActionState
{
public:
	static sf::Vector2i startinPosition;
	static sf::Vector2i currentPosition;
	TurnState* turnState;
	state& gState;

	ActionState(state& gState, TurnState* turnState) : gState(gState), turnState(turnState) {}

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;

	virtual void update() = 0;
	virtual void draw(state& gState) = 0;
};

