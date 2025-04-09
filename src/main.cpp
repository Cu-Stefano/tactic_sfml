#include "headers/mapBuilder.h"
#include "headers/state.h"

/// Hadnle events
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

void handle(const sf::Event::Closed&, state& gs)
{
    gs.window.close();
}

template <typename T>
void handle(const T&, state& gs)
{
    // All unhandled events will end up here
}
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
