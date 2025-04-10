#pragma once
#include "unit.h"
#include <functional>
#include <string>
#include <vector>
#include <optional>

struct Tile : public button
{
    Tile(int tileID, const std::string& tileName, bool walkable, Unit unitOn);

    std::string TileName;
    bool Walkable;
    std::optional<Unit> UnitOn;

    //Path Algorithm attributes
    int G = 0;
    bool passable = true;
    Tile* Parent;
    std::vector<Tile> Neighbours;
};
