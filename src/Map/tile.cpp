#include "../headers/tile.h"

Tile::Tile(const std::string& tileName, bool walkable, Unit* unitOn,
    const Vector2f& pos, const Vector2f& size, const Sprite& spr)
    : Button(pos, size, spr)
{
	TileName = tileName;
	Walkable = walkable;
	UnitOn = unitOn;
}
