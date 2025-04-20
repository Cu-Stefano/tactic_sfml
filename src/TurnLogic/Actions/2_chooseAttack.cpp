#include "../../headers/2_chooseAttack.h"

#include "../../headers/tile.h"
#include "../../headers/unit.h"

ChooseAttack::ChooseAttack(const state& state, const std::vector<Tile*>& enemyNear, Tile* attackingUnit): ActionState(gsState, turnState)
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
	}
}

void ChooseAttack::draw(state& gsState)
{
	for (auto enemy : enemyNear)
	{
		gsState.window.draw(enemy->shape);
	}
}

