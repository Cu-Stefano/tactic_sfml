#include <utility>

#include "../headers/tile.h"
#include "../headers/state.hpp"
#include "../headers/unit.h"

Tile::Tile(std::string tileName, bool walkable, Unit* unitOn,const Vector2f& pos, const Vector2f& size, const Sprite& spr, Sprite pathSpr)
	: Button(pos, size, spr), tileName(std::move(tileName)), walkable(walkable), unitOn(unitOn), path_sprite(std::move(pathSpr))
{}

void Tile::draw(::state& gsState) const
{
	Button::draw(gsState);
}

void Tile::move_unit(Tile* b)
{
	if (unitOn == nullptr) return;

	walkable = true;
	b->walkable = false;
	b->unitOn = unitOn;
	unitOn->an_sprite.sprite->setPosition(b->sprite.getPosition());

	if (unitOn->name == "Boss")
		unitOn->an_sprite.sprite->move({ -27, -32 });
	else
		unitOn->an_sprite.set_pos({ -12, -12 });
	
	b->unitOn->can_move = false;
	b->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);

	unitOn = nullptr;

}
