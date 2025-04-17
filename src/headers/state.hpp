#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "mapLogic.h"
class Tile;


constexpr unsigned window_width = 1400;
constexpr unsigned window_height = 840;

// Define colors as constants
const sf::Color ENEMY_ATTACK_COLOR(0xFFFF4500);
const sf::Color ALLAY_ATTACK_COLOR(52,	151,	163, 190);
const sf::Color ENEMY_PATH_COLOR(0x23A8FA); 
const sf::Color ALLAY_PATH_COLOR(173, 220, 245, 180);
const sf::Color UNIT_MOVED(135, 135, 135, 255);

class state
{
public:
    sf::RenderWindow window;
    int menubar_attack_window_x = window_width - 200;
    int menubar_attack_y = window_height - 200;

    MapLogic maplogic;

    std::vector<std::vector<Tile*>> Map;
    Tile* selected_tile;
    sf::Font font = sf::Font("resources/font/16x16_font.ttf");

    state(unsigned w, unsigned h, const std::string& title): maplogic(*this), selected_tile(nullptr)
    {
        window = sf::RenderWindow(sf::VideoMode({ w, h }), title);
    }

    Tile* getTileFromMousePosition(sf::Vector2f mousePos) const
    {
        int tileX = static_cast<int>(mousePos.x) / 40;
        int tileY = static_cast<int>(mousePos.y) / 40;
        if (isMouseOutOfRange(mousePos))
            return nullptr;
        return Map[tileY][tileX];
    }

    sf::Vector2i getCoordFromTile(Tile* tile) const
    {
		for (int i = 0; i < Map.size(); ++i)
		{
			for (int j = 0; j < Map[i].size(); ++j)
			{
				if (Map[i][j] == tile)
				{
					return {i, j};
				}
			}
		}
		return {-1, -1};
    }

    bool isMouseOutOfRange(sf::Vector2f mousePos) const
    {
       return (mousePos.x > menubar_attack_window_x || mousePos.y > menubar_attack_y || mousePos.x < 0 || mousePos.y < 0);
    }


};


