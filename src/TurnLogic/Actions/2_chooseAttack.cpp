#include "../../headers/2_chooseAttack.h"
#include "../../headers/tile.h"
#include "../../headers/unit.h"
using namespace sf;

ChooseAttack::ChooseAttack(state& gsState, const std::vector<Tile*>& enemyNear, Tile* attackingUnit)
	: ActionState(gsState, turnState)
{
	this->enemyNear = enemyNear;
	this->attackingUnit = attackingUnit;
}
void ChooseAttack::on_enter()
{
}
void ChooseAttack::on_exit()
{
}

void ChooseAttack::update()
{
	for (auto enemy : enemyNear)
	{
		enemy->shape.setOutlineColor(sf::Color::Red);
		enemy->shape.setOutlineThickness(-2);
		enemy->unitOn->an_sprite.sprite_y = 2;
		attackingUnit->unitOn->an_sprite.sprite_y = 2;
	}

	if (isButtonPressed(sf::Mouse::Button::Left) && !preview_selected)
	{
		preview_selected = true;

		Vector2f mousePos = gsState.window.mapPixelToCoords(sf::Mouse::getPosition(gsState.window));
		if (gsState.isMouseOutOfRange(sf::Vector2f(mousePos))) return;
		auto clicked_tile = gsState.get_tile_from_mouse_position(sf::Vector2f(mousePos));

		gsState.attackGui.unitA = attackingUnit;
		gsState.attackGui.unitB = clicked_tile;
	}
	if (isButtonPressed(sf::Mouse::Button::Left) && preview_selected)
	{
		//se clicco sul bottone attack inizio lo stato di attacco
	}
}

void ChooseAttack::draw(state& gsState)
{
	for (auto enemy : enemyNear)
	{
		gsState.window.draw(enemy->shape);
	}
	if (preview_selected)
	{
		gsState.attackGui.draw_units();
		gsState.attackGui.draw_stats();
	}
}

