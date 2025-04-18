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

void Tile::move_unit(Tile* b, std::vector<Tile*> route)
{
    if (unitOn == nullptr) return;
    if (b == this)
    {
        unitOn->an_sprite.sprite_y = 0;
        unitOn->an_sprite.swap_interval = 0.3f; // sec
        unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
        unitOn->canMove = false;
    }
    else
    {
        Unit::IsAnyUnitMoving = true;
        walkable = true;
        b->walkable = false;

        b->unitOn = unitOn;
        b->unitOn->canMove = false;

        // Imposta la posizione di destinazione
        b->unitOn->targetRoute = route;
        b->unitOn->isMoving = true;
        unitOn = nullptr;
    }
}