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
    Tile(const std::string& tileName, bool walkable, Unit* unitOn,
        const Vector2f& pos, const Vector2f& size, const Sprite& spr, const Sprite& path_spr);
    void draw(::state& gState) const;

    void move_unit(Tile* b, std::vector<Tile*> route);

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
