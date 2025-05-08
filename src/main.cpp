#include "headers/mapBuilder.h"
#include "headers/state.hpp"
#include "headers/tile.h"
#include "headers/turnState.hpp"
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

    sf::Sprite weapon_triangle(gs.ui);
    sf::Sprite weapon(gs.ui);
    sf::Sprite nameIcon(gs.ui);
    weapon_triangle.setTextureRect(sf::IntRect({ 0, 0 }, { 0, 0 }));
	weapon.setTextureRect(sf::IntRect({ 0, 0 }, { 0, 0 }));
    nameIcon.setTextureRect(sf::IntRect({ 0, 0 }, { 0, 0 }));

    if (gs.selectedTile != nullptr && gs.selectedTile->unitOn != nullptr)
    {
        // Text for unit name and HP
        unitText.setFillColor(sf::Color::White);  
               unitText.setString(gs.selectedTile->unitOn->name);  
               unitText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) +  
                   ((WINDOW_WIDTH - static_cast<float>(gs.menubar_attack_window_x)) / 2) -  
                   (unitText.getLocalBounds().size.x / 2), 50 });

    	maxHP.setString(std::to_string(gs.selectedTile->unitOn->hp) + "/" );
        maxHP.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 65, 90 });
        gs.window.draw(maxHP);
        maxHP.setString(std::to_string(gs.selectedTile->unitOn->max_hp));
		maxHP.setFillColor(sf::Color::Green);
        maxHP.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 112, 90 });

        // Text for unit statistics
        statsText.setFillColor(sf::Color::White);
        statsText.setString(
            "\n\n\n\nStr:" + std::to_string(gs.selectedTile->unitOn->strength) + "\n\n\n" +
            "Defense:" + std::to_string(gs.selectedTile->unitOn->defense) + "\n\n\n" +
            "Speed:" + std::to_string(gs.selectedTile->unitOn->speed) + "\n\n\n" +
            "Skill:" + std::to_string(gs.selectedTile->unitOn->skill) + "\n\n\n" +
            "Luck:" + std::to_string(gs.selectedTile->unitOn->luck));

        statsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 100 });

        // Text for calculated statistics
        calcStatsText.setFillColor(sf::Color::White);
        calcStatsText.setString(
            "\n\n\nDodge: " + std::to_string(gs.selectedTile->unitOn->get_dodge()) + "\n\n\n" +
            "Hit: " + std::to_string(gs.selectedTile->unitOn->get_hit()) + "\n\n\n" +
            "Attack: " + std::to_string(gs.selectedTile->unitOn->get_attack()) + "\n\n\n" +
            "Crit: " + std::to_string(gs.selectedTile->unitOn->get_crit()));
        calcStatsText.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 26, 380 });

        nameIcon.setTextureRect(sf::IntRect({ 50, 50 }, { 45, 15 }));
		nameIcon.setScale({ 4, 3 });
		nameIcon.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + 13, 45 });

        weapon_triangle.setTextureRect(sf::IntRect({ 154, 8 }, { 46, 42 }));
        weapon_triangle.setScale({ 3, 3 });
        weapon_triangle.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + ((WINDOW_WIDTH - static_cast<float>(gs.menubar_attack_window_x)) / 2) - 68, 685 });

        //draw the unit's weapom
        switch (gs.selectedTile->unitOn->unit_class)
        {
		case swordsman:
            weapon.setTextureRect(sf::IntRect({ 154, 8 }, { 18, 18 }));
			break;
		case warrior:
            weapon.setTextureRect(sf::IntRect({ 182, 8 }, { 18, 18 }));
			break;
		case soldier:
            weapon.setTextureRect(sf::IntRect({ 168, 32 }, {18, 18 }));
			break;
        }

        weapon.setPosition({ static_cast<float>(gs.menubar_attack_window_x) + ((WINDOW_WIDTH - static_cast<float>(gs.menubar_attack_window_x)) / 2) - 36, 600 });
        weapon.setScale({ 4, 4 });

    }
    gs.window.draw(nameIcon);
    gs.window.draw(unitText);
    gs.window.draw(maxHP);
    gs.window.draw(statsText);
    gs.window.draw(calcStatsText);
    gs.window.draw(weapon_triangle);
	gs.window.draw(weapon);

}

void attack_window_draw(state& gs)
{
	gs.attackGui.draw(gs.window);
}

void curr_unit_window_draw(state& gs)
{
	sf::Sprite top_curr_unit_window(gs.ui);
	sf::Sprite curr_unit_window(gs.ui);
	sf::Sprite bottom_curr_unit_window(gs.ui);

	top_curr_unit_window.setTextureRect(sf::IntRect({ 54, 6 }, { 37, 8 }));
	top_curr_unit_window.scale({ 5.6, 5 });
	curr_unit_window.setTextureRect(sf::IntRect({ 54, 13 }, { 37, 20 }));
	curr_unit_window.setScale({ 5.6, 40 });
	bottom_curr_unit_window.setTextureRect(sf::IntRect({ 54, 33 }, { 37, 9 }));
	bottom_curr_unit_window.scale({ 5.6, 5.1 });

	top_curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x), 0 });
	curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x), 30 });
	bottom_curr_unit_window.setPosition({ static_cast<float>(gs.menubar_attack_window_x)  , 795});

	gs.window.draw(top_curr_unit_window);
	gs.window.draw(curr_unit_window);
	gs.window.draw(bottom_curr_unit_window);
}

/// Graphics
void do_gui(state& gs)
{
	curr_unit_window_draw(gs);
    draw_curr_stats(gs);

	attack_window_draw(gs);
}

void do_graphics(state& gs)
{
    gs.window.clear();

    do_gui(gs);
	draw_map(gs);

    gs.TurnSM.current_turnState->draw(gs.window);
    for (auto& allay : allay_list)
    {
        allay->draw(gs.window);
    }
    for (auto& enemy : enemy_list)
    {
        enemy->draw(gs.window);
    }

    gs.window.display();
}

/// Update
void update(state& gs)
{
    update_map(gs);
	gs.TurnSM.update();
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
    gs.selectedTile = gs.map[0][1];

    while (gs.window.isOpen()) // main loop
    {
        while (gs.window.isOpen())
        { // main loop
            while (const std::optional event = gs.window.pollEvent())
            {
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