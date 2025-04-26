#include "../../headers/2_chooseAttack.h"
#include "../../headers/3_attack.h"
#include "../../headers/0_chooseTile.h"
#include "../../headers/tile.h"
#include "../../headers/turnState.hpp"
#include "../../headers/unit.h"

using namespace sf;

ChooseAttack::ChooseAttack(state& gState, TurnState* turnState, const std::vector<Tile*>& enemyNear, Tile* attackingUnit)
	: ActionState(gState, turnState), attackedUnit(nullptr)
{
	this->enemyNear = enemyNear;
	this->attackingUnit = attackingUnit;
}

void ChooseAttack::on_enter()
{
}
void ChooseAttack::on_exit()
{
	for (auto enemy : enemyNear)
	{
		enemy->unitOn->an_sprite.sprite_y = 0;
	}
}

void ChooseAttack::update()
{
	for (auto enemy : enemyNear)
	{
		enemy->shape.setOutlineColor(sf::Color::Red);
		enemy->shape.setOutlineThickness(-2);
		attackingUnit->unitOn->an_sprite.swap_interval = 0.2f;
		enemy->unitOn->an_sprite.swap_interval = 0.2f;
		//enemy->unitOn->an_sprite.sprite_y = 2;
		//attackingUnit->unitOn->an_sprite.sprite_y = 2;
	}

	if (isButtonPressed(sf::Mouse::Button::Left))
	{
		Vector2f mousePos = gState.window.mapPixelToCoords(sf::Mouse::getPosition(gState.window));
		if (gState.isMouseOutOfRange(sf::Vector2f(mousePos)))
		{
			sf::FloatRect bounds = gState.attackGui.attack_text.getGlobalBounds();

			if (bounds.contains({ mousePos.x, mousePos.y }))
				turnState->SetActionState(new Attack(gState, turnState, attackingUnit, attackedUnit, gState.attackGui.unitAStats, gState.attackGui.unitBStats));
		}
		else
		{
			auto clicked_tile = gState.get_tile_from_mouse_position(sf::Vector2f(mousePos));

			if (std::find(enemyNear.begin(), enemyNear.end(), clicked_tile) != enemyNear.end())
			{
				gState.attackGui.unitA = new Unit(*attackingUnit->unitOn);
				attackedUnit = clicked_tile;
				gState.attackGui.unitB = new Unit (*clicked_tile->unitOn);
				gState.attackGui.unitAStats = {};
				gState.attackGui.unitBStats = {};
				gState.attackGui.update();
				preview_selected = clicked_tile->unitOn != nullptr;
			}
			else if (clicked_tile == attackingUnit)
			{
				attackingUnit->move_unit(clicked_tile, {});
				attackingUnit->unitOn->an_sprite.sprite_y = 0;
				attackingUnit->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);

				for (auto enemy : enemyNear)
				{
					enemy->unitOn->an_sprite.sprite_y = 0;
				}

				turnState->SetActionState(new ChooseTile(gState, turnState));
			}
		}
	}
	if (isButtonPressed(sf::Mouse::Button::Right))//back
	{
		for (auto enemy : enemyNear)
		{
			enemy->unitOn->an_sprite.sprite_y = 0;
		}

		attackingUnit->unitOn->an_sprite.sprite_y = 0;
		gState.map[startinPosition.y][startinPosition.x]->unitOn = attackingUnit->unitOn;

		attackingUnit->unitOn->an_sprite.sprite->setPosition(Vector2f{ static_cast<float>(startinPosition.x * 40), static_cast<float>(startinPosition.y * 40) });
		attackingUnit->unitOn->an_sprite.sprite->move(DEFAULT_OFFSET);
		attackingUnit->unitOn = nullptr;

		turnState->SetActionState(new ChooseTile(gState, turnState));
	}
}

void ChooseAttack::draw(state& gState)
{
	for (auto enemy : enemyNear)
	{
		gState.window.draw(enemy->shape);
	}
	if (preview_selected)
	{
		gState.attackGui.draw_units();
		gState.window.draw(*gState.attackGui.attack_button);
		gState.attackGui.draw_stats();
	}
}

