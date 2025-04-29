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

    Button* attack_button; // Cambiato da sf::Sprite* a Button*
    sf::Text attack_text;
    Tile* unitA;
    Tile* unitB;
    std::vector<int> unitAStats{};
    std::vector<int> unitBStats{};
	int bonus = 0;
    bool attack_initiated = false;
    bool first = true;

    void draw_units();
    void draw_stats();

    void draw(sf::RenderWindow& window);
    void update();
};
