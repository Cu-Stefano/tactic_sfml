#pragma once

#include <SFML/Graphics.hpp>
#include "unit.h"

class state;
class Tile;

class AttackGui
{
public:
    AttackGui(state& gState);
    state& gState;

	sf::Sprite* attack_button;
    sf::Text attack_text;
    Unit* unitA;
    Unit* unitB;
    std::vector<int> unitAStats{};
    std::vector<int> unitBStats{};
	int bonus = 0;
    bool attack_initiated = false;

    void draw_units();
    void draw_stats();

    void draw(sf::RenderWindow& window);
    void update();
};
