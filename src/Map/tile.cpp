#include <utility>

#include "../headers/tile.h"
#include "../headers/state.hpp"
#include "../headers/unit.h"

Tile::Tile(std::string tileName, bool walkable, Unit* unitOn,const Vector2f& pos, const Vector2f& size, const Sprite& spr, Sprite pathSpr)
	: Button(pos, size, spr), tileName(std::move(tileName)), walkable(walkable), unitOn(unitOn), path_sprite(std::move(pathSpr))
{}

void Tile::draw(::state& gState) const
{
	Button::draw(gState);
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

        // Imposta la posizione di destinazione
        b->unitOn->targetRoute = route;
        b->unitOn->isMoving = true;
        unitOn = nullptr;
    }
}