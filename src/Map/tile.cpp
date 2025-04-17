#include "../headers/tile.h"
#include "../headers/state.h"

Tile::Tile(const std::string& tileName, bool walkable, Unit* unitOn,
    const Vector2f& pos, const Vector2f& size, const Sprite& spr, Sprite* path_spr)
	: Button(pos, size, spr)
{
	TileName = tileName;
	Walkable = walkable;
	UnitOn = unitOn;
	path_sprite = path_spr;
}

void Tile::draw(::state& gs_state) const
{
	Button::draw(gs_state);
}