#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/MapLogic.h"  
#include "../headers/state.hpp"
#include "../headers/actionState.hpp"
#include "../headers/gameFinished.h"

using namespace sf;

GameFinished::GameFinished(MapLogic* map_logic, sf::String state): TurnState(map_logic->gState)
{
	this->state = new sf::Text(gState.font, state, 40);
	this->state->setPosition({
		static_cast<float>(gState.menubar_attack_window_x / 3), static_cast<float>(gState.menubar_attack_y / 3)
	});
	this->state->setFillColor(sf::Color::White);
}

void GameFinished::update()
{

}

void GameFinished::draw(::state& gState)
{
	gState.window.draw(*state);
}
