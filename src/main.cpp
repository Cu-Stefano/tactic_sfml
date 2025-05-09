#include "headers/mapBuilder.h"
#include "headers/state.hpp"
#include "headers/tile.h"
#include "headers/unit.h"

using namespace sf;

////////////////////////////////////////////////////////////
void draw_curr_stats(state& gs)
{
	sf::Text unitText{ gs.font, "", 15 };
	sf::Text maxHP{ gs.font, "", 15 };
	unitText.setFillColor(sf::Color::White);
	sf::Text statsText{ gs.font, "", 15 };
	statsText.setFillColor(sf::Color::White);
	sf::Text calcStatsText{ gs.font, "", 15 };
	calcStatsText.setFillColor(sf::Color::White);

    Texture traingle = Texture("resources/Ui/Ui_assets.png");
    sf::Sprite weapon_traingle(traingle);
    weapon_traingle.setTextureRect(sf::IntRect({ 0, 0 }, { 0, 0 }));

    if (gs.selected_tile != nullptr && gs.selected_tile->unitOn != nullptr)
    {
        // Text for unit name and HP
        unitText.setFillColor(sf::Color::White);
        unitText.setString(gs.selected_tile->unitOn->name + "\n\n" +
            "HP: " + std::to_string(gs.selected_tile->unitOn->hp) + "/");
        unitText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 50 });

        maxHP.setString(std::to_string(gs.selected_tile->unitOn->max_hp));
		maxHP.setFillColor(sf::Color::Green);
        maxHP.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 133, 80 });

        // Text for unit statistics
        statsText.setFillColor(sf::Color::White);
        statsText.setString(
            "\n\n\n\nStr:" + std::to_string(gs.selected_tile->unitOn->strength) + "\n\n\n" +
            "Defense:" + std::to_string(gs.selected_tile->unitOn->defense) + "\n\n\n" +
            "Speed:" + std::to_string(gs.selected_tile->unitOn->speed) + "\n\n\n" +
            "Skill:" + std::to_string(gs.selected_tile->unitOn->skill) + "\n\n\n" +
            "Luck:" + std::to_string(gs.selected_tile->unitOn->luck));

        statsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 100 });

        // Text for calculated statistics
        calcStatsText.setFillColor(sf::Color::White);
        calcStatsText.setString(
            "\n\n\nDodge: " + std::to_string(gs.selected_tile->unitOn->get_dodge()) + "\n\n\n" +
            "Hit: " + std::to_string(gs.selected_tile->unitOn->get_hit()) + "\n\n\n" +
            "Attack: " + std::to_string(gs.selected_tile->unitOn->get_attack()) + "\n\n\n" +
            "Crit: " + std::to_string(gs.selected_tile->unitOn->get_crit()));
        calcStatsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 380 });

        weapon_traingle.setTextureRect(sf::IntRect({ 155, 9 }, { 44, 38 }));
        weapon_traingle.setScale({ 3, 3 });
        weapon_traingle.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + ((WINDOW_WIDTH - static_cast<float>(gs.menubar_attack_window_x)) / 2) - 66, 690 });

    }
    gs.window.draw(unitText);
	gs.window.draw(maxHP);
    gs.window.draw(statsText);
    gs.window.draw(calcStatsText);
    gs.window.draw(weapon_traingle);

}

void attack_window_draw(state& gs, Texture ui)
{
	gs.attackGui.draw(gs.window);
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
	gs.MapLogic.update();
    for (auto& allay : allay_list)
    {
        allay->update();
    }
    for (auto& enemy : enemy_list)
    {
        enemy->update();
    }
}
////////////////////////////////////////////////////////////


int main()
{
    state gs(WINDOW_WIDTH, WINDOW_HEIGHT, "TacticSFML");
    gs.window.setFramerateLimit(60);

    initialize_map(gs);
    gs.selected_tile = gs.map[0][1];

    while (gs.window.isOpen()) // main loop
    {
        while (gs.window.isOpen())
        { // main loop
            while (const std::optional event = gs.window.pollEvent())
            { // event loop + hevent handler
                if (event->is<sf::Event::Closed>())
                {
                    gs.window.close();
                    break;
                }

                if (const auto* resized = event->getIf<sf::Event::Resized>())
                {
                    if (resized->size.x < WINDOW_WIDTH || resized->size.y < WINDOW_HEIGHT)
                    {
                        gs.window.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
                        continue;
                    }

                    float aspectRatio = static_cast<float>(resized->size.x) / static_cast<float>(resized->size.y);

                    if (aspectRatio <= 1.2f || aspectRatio >= 2.4f)
                    {
                        gs.window.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
                        continue;
                    }

                    sf::View view = gs.window.getView();
                    view.setSize({ static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });

                    gs.window.setView(view);
                }
            }

            update(gs);
            do_graphics(gs);
        }
    }
}