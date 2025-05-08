#pragma once

#include <SFML/Graphics.hpp>

class Button;
class Tile;
class state;

class AttackGui
{
public:
    AttackGui(state& gState);
    state& gState;

    Button* attack_button;
    sf::Text attack_text;

    Tile* unitA;
    Tile* unitB;
    std::vector<int> unitAStats{};
    std::vector<int> unitBStats{};
	int bonus = 0;
    bool attack_initiated = false;

	void initializer(Tile* unitA, Tile* unitB) const;
    void draw_unit(Tile* unit, float x, bool isUnitA) const;
    void draw_units() const;
    void draw_stats();

    void draw(sf::RenderWindow& window) const;
    void update();
};
