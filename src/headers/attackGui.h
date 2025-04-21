#pragma once

#include <SFML/Graphics.hpp>

class state;
class Tile;

class AttackGui
{
public:
    AttackGui(state& gState);

    state& gState;
    Tile* unitA;
    Tile* unitB;

    void draw_units();
    void draw_stats();

    void draw(sf::RenderWindow& window);
    void update();
};
