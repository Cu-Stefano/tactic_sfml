#include "../headers/attackGui.h"
#include "../headers/button.h"
#include "../headers/turnState.hpp"
#include "../headers/2_chooseAttack.h"
#include "../headers/3_attack.h"
#include <iostream>

#include "../headers/enemyTurn.h"
#include "../headers/state.hpp"
#include "../headers/tile.h"
#include "../headers/unit.h"
using namespace sf;

Texture ui = Texture("resources/Ui/Ui_assets.png");

AttackGui::AttackGui(state& gState) : gState(gState), attack_text(gState.font, "ATTACK!", 20)
{
	sf::Sprite buttonSprite(ui);
	buttonSprite.setTextureRect(sf::IntRect({ 97, 50 }, { 46, 13 }));
	buttonSprite.setScale({ 4, 4.5 });
	buttonSprite.setPosition({ gState.menubar_attack_window_x / 4.7f, static_cast<float>(gState.menubar_attack_y) + 68 });

	sf::Vector2f buttonPos = { gState.menubar_attack_window_x / 4.7f , static_cast<float>(gState.menubar_attack_y) + 68 };
	sf::Vector2f buttonSize = { buttonSprite.getGlobalBounds().size.x , buttonSprite.getGlobalBounds().size.y };
	
	attack_button = new Button(buttonPos, buttonSize, buttonSprite);

	attack_button->set_click_function([&]() {
		gState.MapLogic.current_turnState->SetActionState(new Attack(gState, gState.MapLogic.current_turnState, unitA, unitB, gState.attackGui.unitAStats, gState.attackGui.unitBStats));
	});

}

void AttackGui::draw(sf::RenderWindow& window)
{
	sf::Sprite left_attack_window(ui);
	sf::Sprite attack_window(ui);
	sf::Sprite right_attack_window(ui);

	left_attack_window.setTextureRect(sf::IntRect({ 54, 6}, { 7, 37 }));
	left_attack_window.scale({ 5, 5.6 });

	attack_window.setTextureRect(sf::IntRect({ 61, 6 }, { 22, 37 }));
	attack_window.setScale({ 51.5, 5.6 });

	right_attack_window.setTextureRect(sf::IntRect({ 81, 6 }, { 8, 37 }));
	right_attack_window.scale({ 5, 5.6 });

	left_attack_window.setPosition({ 0, static_cast<float>(gState.menubar_attack_y) });
	attack_window.setPosition({ 35, static_cast<float>(gState.menubar_attack_y) });
	right_attack_window.setPosition({ static_cast<float>(gState.menubar_attack_window_x - 39)  , static_cast<float>(gState.menubar_attack_y) });

	gState.window.draw(left_attack_window);
	gState.window.draw(attack_window);
	gState.window.draw(right_attack_window);
}

void AttackGui::initializer(Tile* unitA, Tile* unitB)
{
	gState.attackGui.unitA = unitA;
	gState.attackGui.unitB = unitB;
	gState.attackGui.unitAStats = {};
	gState.attackGui.unitBStats = {};
}

// Disegna unitA
void AttackGui::draw_unit(Tile* unit, float x, bool isUnitA)
{
	if (unit && unit->unitOn)
	{
		float positionY = static_cast<float>(gState.menubar_attack_y) - 20;
		Sprite unit_sprite = *unit->unitOn->an_sprite.sprite;
		if (unit->unitOn->name == "Boss")
		{
			unit_sprite.setScale({ static_cast<float>(isUnitA ? 11 : -11), 11 });
			positionY -= 55;
		}
		else
			unit_sprite.setScale({ static_cast<float>(isUnitA ? 8 : -8), 8 });

		float positionX = isUnitA ? x : (gState.menubar_attack_window_x - x);
		unit_sprite.setPosition({ positionX, positionY });
		gState.window.draw(unit_sprite);
	}
}

void AttackGui::draw_units()
{
	float x = 45.0f;
	if (attack_initiated)
		x = 350.0f;
	else if (unitA->unitOn->type == 0)
		attack_button->draw(gState);

	draw_unit(unitA, x, true);
	draw_unit(unitB, x, false);
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

	a_stats.push_back(unita.hp); // hp rimasti  
    a_stats.push_back(std::max(0, unita.get_attack() - unitb.defense + bonus_a_att));
    a_stats.push_back(std::min(100, unita.get_hit() - unitb.get_dodge() + bonus_a_hit));  
    a_stats.push_back(unita.get_crit());  

	b_stats.push_back(unitb.hp); // hp rimasti  
    b_stats.push_back(std::max(0, unitb.get_attack() - unita.defense + bonus_b_att));
    b_stats.push_back(std::min(100, unitb.get_hit() - unita.get_dodge() + bonus_b_hit));  
    b_stats.push_back(unitb.get_crit());
}

void AttackGui::draw_stats()
{
    std::vector<std::string> statNames = { "HP", "Damage", "Hit", "Crit" };

    sf::Text text { gState.font, "", 16};
    text.setFillColor(sf::Color::White);
    // positions
    float centerX = gState.menubar_attack_window_x / 2.0f;
    float startY = static_cast<float>(gState.menubar_attack_y) + 27.0f;
    float spacing = 40.0f;

	if (unitA->unitOn->type == 0)
	{
		attack_text.setFillColor(sf::Color::White);
		attack_text.setOutlineThickness(1);
    	attack_text.setOutlineColor(sf::Color::Transparent);
    	attack_text.setPosition({ gState.menubar_attack_window_x / 4.2f, static_cast<float>(gState.menubar_attack_y) + 85 });
    	gState.window.draw(attack_text);
	}

    for (int i = 0; i < statNames.size(); ++i)
    {
        float currentY = startY + i * spacing;

		text.setOutlineThickness(1);
		text.setOutlineColor(sf::Color::Transparent);

        if (i == 0)
        {
			text.setOutlineThickness(1);
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
	if (unitA->unitOn->type == 0)
		attack_button->update(gState.window);
}
