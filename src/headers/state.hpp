#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "MapLogic.h"
#include "attackGui.h"
class Tile;

constexpr unsigned WINDOW_WIDTH = 1400;
constexpr unsigned WINDOW_HEIGHT = 840;

constexpr sf::Color ENEMY_ATTACK_COLOR(190, 52, 52, 190);
constexpr sf::Color ALLAY_ATTACK_COLOR(52,	151,	163, 190);
constexpr sf::Color ENEMY_PATH_COLOR(245, 130, 150, 180);
constexpr sf::Color ALLAY_PATH_COLOR(173, 220, 245, 180);
constexpr sf::Color UNIT_MOVED(135, 135, 135, 255);
constexpr sf::Color ROUTE_COLOR(0, 50, 255, 200);
constexpr sf::Color ENEMY_ROUTE_COLOR(255, 0, 50, 200);

class state
{
public:
    sf::RenderWindow window;
    int menubar_attack_window_x = WINDOW_WIDTH - 200;
    int menubar_attack_y = WINDOW_HEIGHT - 200;

    MapLogic MapLogic;
	AttackGui attackGui;
    std::vector<std::vector<Tile*>> map;
    Tile* selected_tile;
    sf::Font font = sf::Font("resources/font/16x16_font.ttf");

	state(unsigned w, unsigned h, const std::string& title) : MapLogic(*this), attackGui(*this), selected_tile(nullptr)
    {
	    window = sf::RenderWindow(sf::VideoMode({w, h}), title);
    }

    Tile* get_tile_from_mouse_position(const sf::Vector2f mousePos) const
    {
        int tileX = static_cast<int>(mousePos.x) / 40;
        int tileY = static_cast<int>(mousePos.y) / 40;
        if (isMouseOutOfRange(mousePos))
            return nullptr;
        return map[tileY][tileX];
    }

    sf::Vector2i getCoordFromTile(const Tile* tile) const
    {
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[i].size(); ++j)
            {
                if (map[i][j] == tile)
                {
                    return { i, j };
                }
            }
        }
        return { -1, -1 };
    }

    bool isMouseOutOfRange(const sf::Vector2f mousePos) const
    {
       return mousePos.x > menubar_attack_window_x || mousePos.y > menubar_attack_y || mousePos.x < 0 || mousePos.y < 0;
    }
};


