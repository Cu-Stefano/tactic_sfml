#include "../headers/MapLogic.h"
#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"
#include "../headers/state.hpp"

MapLogic::MapLogic(state& gs) : gState(gs), current_turnState(nullptr) {
	gState.turn_number = new sf::Text(gs.font, "Turn: " + std::to_string(gs.turn + 1), 20);
	gState.turn_number->setPosition({ static_cast<float>(gs.menubar_attack_window_x / 2) - 68 , 0 });
	set_state(new AllayTurn(gs));
} 

void MapLogic::set_state(TurnState* newTurnState)
{
	if (current_turnState)
		current_turnState->on_exit();
	current_turnState = newTurnState;
	current_turnState->on_enter();
}

void MapLogic::draw(sf::RenderWindow& window) 
{
	current_turnState->draw(window);
}
void MapLogic::update()
{
	current_turnState->update();
}
