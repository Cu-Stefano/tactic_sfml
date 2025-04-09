#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp> 

#include "headers/mapUtilities.h"
#include "headers/button.h"

////////////////////////////////////////////////////////////
/// Utility

const unsigned window_width = 1400;
const unsigned window_height = 840;

///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// GUI State

struct state
{
    sf::RenderWindow window;
    int menubar_Cunit_x = window_width - 200;
    int menubar_attack_y = window_height - 260;

    // Matrice di bottoni per la mappa
    std::vector<std::vector<Button>> Map;

    state(unsigned w, unsigned h, std::string title)
    {
        window = sf::RenderWindow(sf::VideoMode({ w, h }), title);
    }
};

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
void handle(const sf::Event::Resized& resized, state& gs)
{
    if (resized.size.x < window_width || resized.size.y < window_height)
    {
        gs.window.setSize({ window_width, window_height });
        return;
    }

    float aspectRatio = static_cast<float>(resized.size.x) / static_cast<float>(resized.size.y);

    if (aspectRatio <= 1.2f || aspectRatio >= 2.4f)
    {
        gs.window.setSize({ window_width, window_height });
        return;
    }

    sf::View view = gs.window.getView();
    view.setSize({ static_cast<float>(resized.size.x), static_cast<float>(resized.size.y) });

    gs.window.setView(view);
}

template <typename T>
void handle(const T&, state& gs)
{
    // All unhandled events will end up here
}
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////

/// Graphics
void do_gui(state& gs)
{
    sf::RectangleShape Cunit(sf::Vector2f(window_width - gs.menubar_Cunit_x, window_height));
    Cunit.setPosition({ static_cast<float>(gs.menubar_Cunit_x), 0 });
    Cunit.setFillColor(sf::Color::Magenta);
    gs.window.draw(Cunit);

    sf::RectangleShape attack(sf::Vector2f(gs.menubar_Cunit_x, window_height - gs.menubar_attack_y));
    attack.setPosition({ 0, static_cast<float>(gs.menubar_attack_y) });
    attack.setFillColor(sf::Color::Yellow);
    gs.window.draw(attack);
}

void initialize_Map(state& gs)
{
    float tileSize = 40.0f; 
    float x = 0.0f, y = 0.0f;

    auto map = map_generator();
    for (size_t i = 0; i < map.size(); ++i)
    {
        std::vector<Button> row;
        x = 0.0f;
        for (size_t j = 0; j < map[i].size(); ++j)
        {
            Button button({ x, y }, { tileSize, tileSize });

            switch (map[i][j])
            {
            case 2:
                button.shape.setFillColor(sf::Color::Black);
                break;
            case 3:
                button.shape.setFillColor(sf::Color::Blue);
                break;
            default:
                button.shape.setFillColor(sf::Color::Green);
                break;
            }

            //evento di prova
            button.set_click_function([i, j]() {
                std::cout << "Button clicked at (" << i << ", " << j << ")" << std::endl;
                });

            row.push_back(button);
            x += tileSize; 
        }
        gs.Map.push_back(row);
        y += tileSize; 
    }
}

void draw_map(state& gs)
{
    for (auto& row : gs.Map)
    {
        for (auto& button : row)
        {
            button.update(gs.window);
            button.draw(gs.window);
        }
    }
}

void do_graphics(state& gs)
{
    gs.window.clear();
    do_gui(gs);
    draw_map(gs);

    gs.window.display();
}

////////////////////////////////////////////////////////////


int main()
{
    state gs(window_width, window_height, "TacticSFML");
    gs.window.setFramerateLimit(60);

    // Inizializza i bottoni
    initialize_Map(gs);

    while (gs.window.isOpen()) // main loop
    {
        gs.window.handleEvents([&](const auto& event)
            { handle(event, gs); });

        do_graphics(gs);
    }
}
