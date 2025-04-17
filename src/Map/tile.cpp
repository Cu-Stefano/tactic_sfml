#include "../headers/tile.h"
#include "../headers/state.hpp"
#include "../headers/unit.h"

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



    switch (UnitOn->type)
    {
    case 0:
		//remove the unit from the allay list
		allay_list.erase(std::remove(allay_list.begin(), allay_list.end(), UnitOn), allay_list.end());
		allay_list.push_back(b->UnitOn);
        break;
    case 1:
		//remove the unit from the enemy list
		enemy_list.erase(std::remove(enemy_list.begin(), enemy_list.end(), UnitOn), enemy_list.end());
		enemy_list.push_back(b->UnitOn);
        break;
    default:
        break;
    }

	UnitOn = nullptr;

}
