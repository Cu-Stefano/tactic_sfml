#include "../headers/attackGui.h"

#include <iostream>

#include "../headers/state.hpp"
#include "../headers/tile.h"
#include "../headers/unit.h"
using namespace sf;

Texture ui = Texture("resources/Ui/Ui_assets.png");

AttackGui::AttackGui(state& gState): gState(gState), attack_text(gState.font, "  ATTACK! ", 20)
{
	attack_button = new Sprite(ui);
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
	float x = 45;
	if (attack_initiated)
		x = 350;

	Sprite unitA_sprite = *unitA->unitOn->an_sprite.sprite;
	Sprite unitB_sprite = *unitB->unitOn->an_sprite.sprite;

	unitA_sprite.setScale({ 8, 8 });
	unitA_sprite.setPosition({ x, static_cast<float>(gState.menubar_attack_y) - 20 });

	unitB_sprite.setScale({ -8, 8 });
	unitB_sprite.setPosition({ static_cast<float>(gState.menubar_attack_window_x - x)  , static_cast<float>(gState.menubar_attack_y) - 20});
	gState.window.draw(unitA_sprite);
	gState.window.draw(unitB_sprite);

	//draw attack button

	attack_button->setTextureRect(sf::IntRect({ 0, 130 }, { 48, 12 }));
	attack_button->setScale({ 3.5, 4.5 });
	attack_button->setPosition({ gState.menubar_attack_window_x / 4.1f, static_cast<float>(gState.menubar_attack_y) + 68 });
}

void calculate_attack_stats(Unit unita, Unit unitb, std::vector<int>& a_stats, std::vector<int>& b_stats, int& bonus)
{
	int bonus_a_att = 0, bonus_a_hit = 0;
	int bonus_b_att = 0, bonus_b_hit = 0;

	//triangolo delle armi spada > ascia > lancia > spada ...
	int a_weapon_type = unita.equiped_weapon->type;
	int b_weapon_type = unitb.equiped_weapon->type;

	if (b_weapon_type == (a_weapon_type + 1) % 3)
	{
		bonus = 1; // unitA ha il vantaggio
		bonus_a_att = 3;
		bonus_a_hit = 10;

		bonus_b_hit = -10;
		bonus_b_att = -2;
	}
	else if (a_weapon_type == (b_weapon_type + 1) % 3)
	{
		bonus = 2; // unitA ha lo svantaggio
		bonus_b_att = 3;
		bonus_b_hit = 10;

		bonus_a_hit = -10;
		bonus_a_att = -2;
	}

	int damage = std::max(0, unita.get_attack() - unitb.defense + bonus_a_att);

	a_stats.push_back(std::max(0, unita.hp - damage)); // hp rimasti  
    a_stats.push_back(damage);  
    a_stats.push_back(std::min(100, unita.get_hit() - unitb.get_dodge() + bonus_a_hit));  
    a_stats.push_back(unita.get_crit());  

	damage = std::max(0, unitb.get_attack() - unita.defense + bonus_b_att);
    b_stats.push_back(damage);  
    b_stats.push_back(std::max(0, unitb.hp - damage)); // hp rimasti  
    b_stats.push_back(std::min(100, unitb.get_hit() - unita.get_dodge() + bonus_b_hit));  
    b_stats.push_back(unitb.get_crit());
}

void AttackGui::draw_stats()
{
    std::vector<std::string> statNames = { "HP", "Damage", "Hit", "Crit" };

    sf::Text text { gState.font, "", 16};
    text.setFillColor(sf::Color::White);
	attack_text.setFillColor(sf::Color::White);
    // positions
    float centerX = gState.menubar_attack_window_x / 2.0f;
    float startY = static_cast<float>(gState.menubar_attack_y) + 27.0f;
    float spacing = 40.0f;

	attack_text.setOutlineThickness(1);
	attack_text.setOutlineColor(sf::Color::Black);
	attack_text.setPosition({ gState.menubar_attack_window_x / 4.4f, static_cast<float>(gState.menubar_attack_y) + 85 });
	gState.window.draw(attack_text);

    for (int i = 0; i < statNames.size(); ++i)
    {
        float currentY = startY + i * spacing;

		text.setOutlineThickness(1);
		text.setOutlineColor(sf::Color::Transparent);

        if (i == 0)
        {
			text.setOutlineThickness(1);
			text.setOutlineColor(sf::Color::Black);
			text.setCharacterSize(20);
        }
        else
        {
			text.setCharacterSize(16);
			text.setFillColor(sf::Color::White);
        }

        // stats names
        text.setString(statNames[i]);
        text.setPosition({ centerX - text.getLocalBounds().size.x / 2.0f, currentY });
        gState.window.draw(text);

		if (i == 1 || i == 2)
		{
			text.setFillColor(sf::Color::White);
			switch (bonus)  
			{
			case 1: //unitA ha il vantagggio sul triangolo
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Green);
				break;  
			case 2:  //unitA ha il svantagggio sul triangolo
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Red);
				break;  
			default:  
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Transparent);
				break;  
			}
		}

        // unitA 
        text.setString(std::to_string(unitAStats[i]));
        text.setPosition({ centerX - 100.0f - text.getLocalBounds().size.x, currentY });
		gState.window.draw(text);

		if (i == 1 || i == 2)
		{
			text.setFillColor(sf::Color::White);
			switch (bonus)
			{
			case 1: //unitB ha il svantagggio sul triangolo
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Red);
				break;
			case 2:  //unitB ha il vantagggio sul triangolo
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Green);
				break;
			default:
				text.setOutlineThickness(1);
				text.setOutlineColor(sf::Color::Transparent);
				break;
			}
		}

        // unitB 
        text.setString(std::to_string(unitBStats[i]));
        text.setPosition({ centerX + 100.0f, currentY });
        gState.window.draw(text);
    }
}


void AttackGui::update()  
{  
   calculate_attack_stats(*unitA->unitOn, *unitB->unitOn, unitAStats, unitBStats, bonus);  
   attack_text.getLocalBounds();  
}
