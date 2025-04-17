#include "../headers/tile.h"
#include "../headers/state.hpp"
#include "../headers/unit.h"

Tile::Tile(const std::string& tileName, bool walkable, Unit* unitOn,
    const Vector2f& pos, const Vector2f& size, const Sprite& spr, Sprite* path_spr)
	: Button(pos, size, spr), UnitOn(unitOn), path_sprite(path_spr), Walkable(walkable), TileName(tileName){}

void Tile::draw(::state& gs_state) const
{
	Button::draw(gs_state);
}

void Tile::move_unit(Tile* b)
{
	if (UnitOn == nullptr) return;

	Walkable = true;
	b->Walkable = false;
	b->UnitOn = UnitOn;
	UnitOn->an_sprite.sprite->setPosition(b->sprite.getPosition());

	if (UnitOn->name == "Boss")
		UnitOn->an_sprite.sprite->move({ -27, -32 });
	else
		UnitOn->an_sprite.set_pos({ -12, -12 });
	
	b->UnitOn->can_move = false;
	b->UnitOn->an_sprite.sprite->setColor(UNIT_MOVED);

	UnitOn = nullptr;

}
