#include "../headers/attackGui.h"
#include "../headers/state.hpp"
#include "../headers/tile.h"
#include "../headers/unit.h"
using namespace sf;

Texture ui = Texture("resources/Ui/Ui_assets.png");


AttackGui::AttackGui(state& gState): gState(gState)
{
}

void AttackGui::draw(sf::RenderWindow& window)
{
	sf::Sprite left_attack_window(ui);
	sf::Sprite attack_window(ui);
	sf::Sprite right_attack_window(ui);

	left_attack_window.setTextureRect(sf::IntRect({ 54, 6 }, { 7, 36 }));
	left_attack_window.scale({ 5, 5.5 });

	attack_window.setTextureRect(sf::IntRect({ 61, 6 }, { 22, 36 }));
	attack_window.setScale({ 51.5, 5.5 });

	right_attack_window.setTextureRect(sf::IntRect({ 81, 6 }, { 8, 36 }));
	right_attack_window.scale({ 5, 5.5 });

	left_attack_window.setPosition({ 0, static_cast<float>(gState.menubar_attack_y) });
	attack_window.setPosition({ 35, static_cast<float>(gState.menubar_attack_y) });
	right_attack_window.setPosition({ static_cast<float>(gState.menubar_attack_window_x - 39)  , static_cast<float>(gState.menubar_attack_y) });

	gState.window.draw(left_attack_window);
	gState.window.draw(attack_window);
	gState.window.draw(right_attack_window);
}

void AttackGui::draw_units()
{
	Sprite unitA_sprite = *unitA->unitOn->an_sprite.sprite;
	Sprite unitB_sprite = *unitB->unitOn->an_sprite.sprite;

	unitA_sprite.setScale({ 8, 8 });
	unitA_sprite.setPosition({ 40, static_cast<float>(gState.menubar_attack_y) - 20 });

	unitB_sprite.setScale({ -8, 8 });
	unitB_sprite.setPosition({ static_cast<float>(gState.menubar_attack_window_x - 50)  , static_cast<float>(gState.menubar_attack_y) - 20});
	gState.window.draw(unitA_sprite);
	gState.window.draw(unitB_sprite);

}

void AttackGui::draw_stats()
{
    std::vector<std::string> statNames = { "HP", "Damage", "Hit", "Crit" };

    // placeholder values 
    std::vector<int> unitAStats = { 100, 50, 30, 20 };
    std::vector<int> unitBStats = { 90, 45, 35, 25 };


    sf::Text text { gState.font, "", 20};
    text.setFillColor(sf::Color::White);

    // positions
    float centerX = gState.menubar_attack_window_x / 2.0f;
    float startY = static_cast<float>(gState.menubar_attack_y) + 25.0f;
    float lineSpacing = 40.0f;

    for (int i = 0; i < statNames.size(); ++i)
    {
        float currentY = startY + i * lineSpacing;

        if (i == 0)
            text.setFillColor(sf::Color::Green);  // verde per gli HP
        else
            text.setFillColor(sf::Color::White); 

        // stats names 
        text.setString(statNames[i]);
        text.setPosition({ centerX - text.getLocalBounds().size.x / 2.0f, currentY });
        gState.window.draw(text);

        // unitA 
        text.setString(std::to_string(unitAStats[i]));
        text.setPosition({ centerX - 100.0f - text.getLocalBounds().size.x, currentY });
        gState.window.draw(text);

        // unitB 
        text.setString(std::to_string(unitBStats[i]));
        text.setPosition({ centerX + 100.0f, currentY });
        gState.window.draw(text);
    }
}


void AttackGui::update()
{
	
}
