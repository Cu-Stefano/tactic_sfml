#pragma once
#include "button.h"
#include "unit.h"
#include <functional>
#include <string>
#include <vector>
#include <optional>

class Tile : public Button {
public:
    Tile() = default;

    Tile(const std::string& tileName, bool walkable, Unit* unitOn,
        const Vector2f& pos, const Vector2f& size, const Sprite& spr);

    std::string TileName;
    bool Walkable;
    Unit* UnitOn;

    // Path Algorithm attributes
    int G = 0;
    bool passable = true;
    Tile* Parent = nullptr;
    std::vector<Tile*> Neighbours;
};
