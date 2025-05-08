#include "../headers/TurnSM.h"
#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"
#include "../headers/state.hpp"

TurnSM::TurnSM(state& gs) : gState(gs), current_turnState(nullptr) {
	gState.turnNumber = new sf::Text(gs.font, "Turn: " + std::to_string(gs.turn + 1), 20);
	gState.turnNumber->setPosition({ static_cast<float>(gs.menubar_attack_window_x / 2) - 68 , 0 });

	set_state(new AllayTurn(gs));
} 

void TurnSM::set_state(TurnState* newTurnState)
{
	if (current_turnState)
		current_turnState->on_exit();
	current_turnState = newTurnState;
	current_turnState->on_enter();
}

void TurnSM::draw(sf::RenderWindow& window) const
{
	current_turnState->draw(window);
}
void TurnSM::update() const
{
	current_turnState->update();
}
