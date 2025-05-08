#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/state.hpp"
#include "../headers/gameFinished.h"

using namespace sf;

GameFinished::GameFinished(state& gs, sf::String state): TurnState(gs)
{
	this->win_state = new sf::Text(gState.font, state, 40);
	this->win_state->setPosition({
		static_cast<float>(gState.menubar_attack_window_x / 3), static_cast<float>(gState.menubar_attack_y / 3)
	});
	this->win_state->setFillColor(sf::Color::White);

	if (state == "GAME OVER")
		gs.turnsoundSound.setBuffer(gs.gameoverBuffer);
	else
		gs.turnsoundSound.setBuffer(gs.winBuffer);

	gs.turnsoundSound.setVolume(25);
	gs.turnsoundSound.setLooping(true);
	gs.turnsoundSound.play();
}

void GameFinished::on_enter()
{
}

void GameFinished::on_exit()
{
}

void GameFinished::SetActionState(ActionState* action)
{
	TurnState::SetActionState(action);
}

void GameFinished::update()
{

}

void GameFinished::draw(sf::RenderWindow& window)
{
	gState.window.draw(*win_state);
}
