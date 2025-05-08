#include "../headers/turnState.hpp"
#include "../headers/allayTurn.h"  
#include "../headers/enemyTurn.h"  
#include "../headers/state.hpp"
#include "../headers/actionState.hpp"
#include "../headers/0_chooseTile.h"
#include "../headers/tile.h"

using namespace sf;

class Turnstate;
class Turnstate;
class ActionState;
class ChooseTile;

AllayTurn::AllayTurn(state& gs) : TurnState(gs), allay_turn_text(nullptr)
{
	CurrentActionState = nullptr;
	
	if (!ui.loadFromFile("resources/Ui/Ui_assets.png")) {
		throw std::runtime_error("Failed to load texture");
	}

	Sprite speedSprite = Sprite(ui);
	speedSprite.setTextureRect(IntRect({ 189, 56 }, { 18, 18 }));
	speedSprite.setScale({ 3, 3 });
	speedSprite.setPosition({ 570, 26 });
	speedUpButton = new Button({570, 26 }, { 54, 54 }, speedSprite);
	speedUpButton->set_click_function([&]() {
		static bool speed = false;
		if (speed) {
			speedUpButton->sprite.setTextureRect(IntRect({ 189, 56 }, { 18, 18 }));
			speed = false;
			UNITS_SPEED = 170.0f;
			Unit::move_speed = UNITS_SPEED;
		}
		else {
			speedUpButton->sprite.setTextureRect(IntRect({ 168, 56 }, { 18, 18 }));
			speed = true;
			UNITS_SPEED = 340.0f;
			Unit::move_speed = UNITS_SPEED;
		}
		});
}

void AllayTurn::on_enter()
{
	gState.turn++;
	gState.turnNumber->setString("Turn: " + std::to_string(gState.turn));
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
	speedUpButton->update(gState.window);

	if (textClock.getElapsedTime().asSeconds() <= 3.0f)
	{
		allay_turn_text = new sf::Text(gState.font, "ALLAY TURN", 40);
		allay_turn_text->setPosition({ gState.menubar_attack_window_x / 3, gState.menubar_attack_y / 3 });
		allay_turn_text->setFillColor(sf::Color::White);
		return;
	}
	allay_turn_text->setFillColor(sf::Color::Transparent);
	
	CurrentActionState->update();
}  

void AllayTurn::draw(sf::RenderWindow& window)
{
	speedUpButton->draw(window);

	gState.window.draw(*gState.turnNumber);
	CurrentActionState->draw(window);
	if (allay_turn_text)
		gState.window.draw(*allay_turn_text);
}