#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/MapLogic.h"  
#include "../headers/state.hpp"
#include "../headers/actionState.hpp"
#include "../headers/0_chooseTile.h"
#include "../headers/tile.h"
#include "../headers/unit.h"

using namespace sf;

class Turnstate;
class ActionState;
class ChooseTile;

AllayTurn::AllayTurn(MapLogic* map_logic) : TurnState(map_logic->gState), allay_turn_text(nullptr)
{
	this->map_logic = map_logic;
	CurrentActionState = nullptr;
}

void AllayTurn::on_enter()
{
	gState.turn++;
	gState.turn_number->setString("Turn: " + std::to_string(gState.turn));
	textClock = sf::Clock();
	SetActionState(new ChooseTile(gState, this));
}  

void AllayTurn::on_exit()
{
	for (auto unit : allay_list)
	{
		unit->canMove = true;
		unit->an_sprite.sprite->setColor(Color::White);
	}
}

void AllayTurn::SetActionState(ActionState* action)
{
	if (CurrentActionState != nullptr)
	{
		CurrentActionState->on_exit();
	}
	CurrentActionState = action;
	CurrentActionState->on_enter();
}

void AllayTurn::update()
{
	if (textClock.getElapsedTime().asSeconds() <= 3.0f)
	{
		allay_turn_text = new sf::Text(gState.font, "ALLAY TURN", 40);
		allay_turn_text->setPosition({ static_cast<float>(gState.menubar_attack_window_x / 3), static_cast<float>(gState.menubar_attack_y / 3) });
		allay_turn_text->setFillColor(sf::Color::White);
		return;
	}
	allay_turn_text->setFillColor(sf::Color::Transparent);
	
	CurrentActionState->update();
}  

void AllayTurn::draw(state& gState)
{
	gState.window.draw(*gState.turn_number);
	if (allay_turn_text)
		gState.window.draw(*allay_turn_text);
	CurrentActionState->draw(gState);
}
