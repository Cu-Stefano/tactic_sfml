#include "headers/mapBuilder.h"
#include "headers/state.h"

/// Handle events
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
void draw_curr_stats(state& gs)
{
    if (gs.selected_tile->UnitOn != nullptr)
    {
        // Text for unit name and HP
        sf::Text unitText{ gs.font, "", 15 };
        unitText.setFillColor(sf::Color::White);
        unitText.setString(gs.selected_tile->UnitOn->name + "\n\n" +
            "HP: " + std::to_string(gs.selected_tile->UnitOn->hp) + "/" + std::to_string(gs.selected_tile->UnitOn->max_hp));
        unitText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 50 });
        gs.window.draw(unitText);

        // Text for unit statistics
        sf::Text statsText{ gs.font, "", 15 };
        statsText.setFillColor(sf::Color::White);
        statsText.setString(
            "\n\n\n\nStr:" + std::to_string(gs.selected_tile->UnitOn->strength) + "\n\n\n" +
            "Defense:" + std::to_string(gs.selected_tile->UnitOn->defense) + "\n\n\n" +
            "Speed:" + std::to_string(gs.selected_tile->UnitOn->speed) + "\n\n\n" +
            "Skill:" + std::to_string(gs.selected_tile->UnitOn->skill) + "\n\n\n" +
            "Luck:" + std::to_string(gs.selected_tile->UnitOn->luck));

        statsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 100 });
        gs.window.draw(statsText);

        // Text for calculated statistics
        sf::Text calcStatsText{ gs.font, "", 15 };
        calcStatsText.setFillColor(sf::Color::White);
        calcStatsText.setString(
            "\n\n\nDodge: " + std::to_string(gs.selected_tile->UnitOn->Get_Dodge()) + "\n\n\n" +
            "Hit: " + std::to_string(gs.selected_tile->UnitOn->Get_Hit()) + "\n\n\n" +
            "Attack: " + std::to_string(gs.selected_tile->UnitOn->Get_Attack()) + "\n\n\n" +
            "Crit: " + std::to_string(gs.selected_tile->UnitOn->Get_Crit()));
        calcStatsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 380 });
        gs.window.draw(calcStatsText);
    }
}

void attack_window_draw(state& gs, Texture ui)
{
    sf::Sprite left_attack_window(ui);
    sf::Sprite attack_window(ui);
    sf::Sprite right_attack_window(ui);

	left_attack_window.setTextureRect(sf::IntRect({ 54, 6 }, { 7, 36 }));
	left_attack_window.scale({ 5, 5.6});
	attack_window.setTextureRect(sf::IntRect({ 61, 6 }, { 22, 36 }));
	attack_window.setScale({ 51.36, 5.6 });
	right_attack_window.setTextureRect(sf::IntRect({ 81, 6 }, { 8, 36 }));
	right_attack_window.scale({ 5, 5.6 });

	left_attack_window.setPosition({ 0, static_cast<float>(gs.menubar_attack_y) });
	attack_window.setPosition({ 35, static_cast<float>(gs.menubar_attack_y) });
	right_attack_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x - 39)  , static_cast<float>(gs.menubar_attack_y) });

	gs.window.draw(left_attack_window);
	gs.window.draw(attack_window);
	gs.window.draw(right_attack_window);
}

void curr_unit_window_draw(state& gs, Texture ui)
{
	sf::Sprite top_curr_unit_window(ui);
	sf::Sprite curr_unit_window(ui);
	sf::Sprite bottom_curr_unit_window(ui);

	top_curr_unit_window.setTextureRect(sf::IntRect({ 54, 6 }, { 37, 8 }));
	top_curr_unit_window.scale({ 5.6, 5 });
	curr_unit_window.setTextureRect(sf::IntRect({ 54, 13 }, { 37, 20 }));
	curr_unit_window.setScale({ 5.6, 40 });
	bottom_curr_unit_window.setTextureRect(sf::IntRect({ 54, 33 }, { 37, 9 }));
	bottom_curr_unit_window.scale({ 5.6, 5 });

	top_curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x), 0 });
	curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x), 30 });
	bottom_curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x)  , 797});

	gs.window.draw(top_curr_unit_window);
	gs.window.draw(curr_unit_window);
	gs.window.draw(bottom_curr_unit_window);
}

/// Graphics
void do_gui(state& gs)
{
    Texture ui = Texture("resources/Ui/Ui_assets.png");

	curr_unit_window_draw(gs, ui);
    draw_curr_stats(gs);

        attack_window_draw(gs, ui);
}

void do_graphics(state& gs)
{
    gs.window.clear();
    do_gui(gs);
	draw_map(gs);

    gs.window.display();
}

void update(state& gs)
{
    update_map(gs);
}
////////////////////////////////////////////////////////////

int main()
{
    state gs(window_width, window_height, "TacticSFML");
    gs.window.setFramerateLimit(60);

	initialize_Map(gs);
    gs.selected_tile = &gs.Map[0][1];

    while (gs.window.isOpen()) // main loop
    {
        gs.window.handleEvents([&](const auto& event)
            { handle(event, gs); });
        update(gs);
        do_graphics(gs);
    }
}
