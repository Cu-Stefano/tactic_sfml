#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "mapLogic.h"

constexpr unsigned window_width = 1400;
constexpr unsigned window_height = 840;

// Define colors as constants
const sf::Color ENEMY_ATTACK_COLOR(0xFFFF4500);
const sf::Color ALLAY_ATTACK_COLOR(52,	151,	163, 190);
const sf::Color ENEMY_PATH_COLOR(0x23A8FA); 
const sf::Color ALLAY_PATH_COLOR(173, 220, 245, 180);


class state
{
public:
    sf::RenderWindow window;
    int menubar_attack_window_x = window_width - 200;
    int menubar_attack_y = window_height - 200;

    MapLogic maplogic;

    std::vector<std::vector<Tile*>> Map;
    Tile* selected_tile;
    Font font = Font("resources/font/16x16_font.ttf");

    state(unsigned w, unsigned h, const std::string& title): maplogic(*this), selected_tile(nullptr)
    {
        window = sf::RenderWindow(sf::VideoMode({ w, h }), title);
    }

    Tile* getTileFromMousePosition(Vector2f mousePos)
    {
        int tileX = static_cast<int>(mousePos.x) / 40;
        int tileY = static_cast<int>(mousePos.y) / 40;
        if (tileX < 0 || tileX >= window_width / 40 || tileY < 0 || tileY >= window_height / 40)
            return nullptr;
        return Map[tileY][tileX];
    }
};


