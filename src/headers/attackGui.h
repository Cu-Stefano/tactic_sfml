#pragma once

#include <SFML/Graphics.hpp>

class state;
class Tile;

class AttackGui
{
public:
    AttackGui(state& gState);
    state& gState;

    sf::Text attack_text;
    Tile* unitA;
    Tile* unitB;
    std::vector<int> unitAStats{};
    std::vector<int> unitBStats{};
	int bonus = 0;

    void draw_units();
    void draw_stats();

    void draw(sf::RenderWindow& window);
    void update();
};
