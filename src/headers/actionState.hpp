#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class state;
class TurnState;

class ActionState
{
public:
	TurnState* turnState;
	state& gsState;
	sf::Vector2i startinPosition;
	sf::Vector2i currentPosition;

	ActionState(state& gsState, TurnState* turnState) : gsState(gsState), turnState(turnState) {}

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;

	virtual void update() = 0;
	virtual void draw(state& gsState) = 0;
};