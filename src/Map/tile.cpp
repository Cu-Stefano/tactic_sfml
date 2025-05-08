#include "../headers/tile.h"
#include "../headers/state.hpp"
#include "../headers/unit.h"


Tile::Tile(const std::string& tileName, bool walkable, Unit* unitOn,
    const Vector2f& pos, const Vector2f& size, const Sprite& spr, const Sprite& path_spr)
    : Button(pos, size, spr), path_sprite(path_spr),
    tileName(tileName), walkable(walkable), unitOn(unitOn)
{
}

void Tile::draw(::state& gState) const
{
	Button::draw(gState.window);
}

void Tile::move_unit(Tile* b, std::vector<Tile*> route)
{
    if (unitOn == nullptr) return;
    if (b == this)
    {
       unitOn->has_moved();
       unitOn->canMove = false;
       unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
       Unit::hasSomeActionBeenStared = true;
    }
    else
    {
        Unit::IsAnyUnitMoving = true;
        walkable = true;
        b->walkable = false;

        b->unitOn = unitOn;

        b->unitOn->targetRoute = route;
        b->unitOn->isMoving = true;
        unitOn = nullptr;
    }
}