#pragma once
#include "button.h"
#include "state.hpp"
#include <string>
#include <vector>

class Unit;
class Button;

class Tile : public Button {
public:
    Tile() = default;
    Tile(std::string tileName, bool walkable, Unit* unitOn, const Vector2f& pos, const Vector2f& size, const Sprite& spr, Sprite pathSpr);

    void draw(::state& gsState) const;

    void move_unit(Tile* b);

    std::string tileName;
    bool walkable;
    Unit* unitOn;

    // Path Algorithm attributes
    int G = 0;
    bool passable = true;
    Tile* Parent = nullptr;
    std::vector<Tile*> neighbours;
    Sprite path_sprite;
};
