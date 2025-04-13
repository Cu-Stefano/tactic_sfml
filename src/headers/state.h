#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "mapLogic.h"

constexpr unsigned window_width = 1400;
constexpr unsigned window_height = 840;

class state
{
public:
    sf::RenderWindow window;
    int menubar_attack_window_x = window_width - 200;
    int menubar_attack_y = window_height - 200;

    MapLogic maplogic;

    std::vector<std::vector<Tile>> Map;
    Tile* selected_tile;
    Font font = Font("resources/font/16x16_font.ttf");

    state(unsigned w, unsigned h, const std::string& title): maplogic(*this), selected_tile(nullptr)
    {
        window = sf::RenderWindow(sf::VideoMode({ w, h }), title);
    }
};

