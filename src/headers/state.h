#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"

const unsigned window_width = 1400;
const unsigned window_height = 840;

struct state
{
    sf::RenderWindow window;
    int menubar_Cunit_x = window_width - 200;
    int menubar_attack_y = window_height - 200;

    // Matrice di bottoni per la mappa
    std::vector<std::vector<Button>> Map;

    state(unsigned w, unsigned h, std::string title)
    {
        window = sf::RenderWindow(sf::VideoMode({ w, h }), title);
    }
};
