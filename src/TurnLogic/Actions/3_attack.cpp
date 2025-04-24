#include "../../headers/3_attack.h"
#include "../../headers/tile.h"
#include "../../headers/actionState.hpp"
#include "../../headers/0_chooseTile.h"
#include "../../headers/turnState.hpp"
#include "../../headers/unit.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

Attack::Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB, std::vector<int> aStats, std::vector<int> bStats)
    : ActionState(state, turnState), unitA(unitA), unitB(unitB), aStats(aStats), bStats(bStats)
{
    srand(static_cast<unsigned>(time(nullptr)));
}


void Attack::on_enter()
{
    gState.attackGui.attack_initiated = true;
    // Simulate unitA's attack on unitB
    if (rand() % 100 < aStats[2]) // Hit chance of unitA
    {
        int damage = aStats[1];
        auto ran = rand() % 100;
        if (ran% 100 < aStats[3]) // Crit chance of unitA
        {
            damage *= 3; // Critical damage
        }

        bStats[0] -= damage;
        unitB->unitOn->hp = std::max(0, bStats[1]);

        // Set flash for hit unit
        B_was_hit = true;

        if (unitB->unitOn->hp <= 0)
        {
            // Unit B died
            unitB->unitOn = nullptr;
            attackFinished = true;
            return;
        }
    }

    // Simulate unitB's counterattack (if still alive)
    if (unitB->unitOn && rand() % 100 < bStats[2]) // Hit chance of unitB
    {
        int damage = bStats[1];
		auto ran = rand() % 100;
        //if (ran % 100 < bStats[3]) // Crit chance of unitB
        //{
        //    damage *= 3; // Critical damage
        //}

        aStats[1] -= damage;
        unitA->unitOn->hp = std::max(0, aStats[1]);

        // Set flash for hit unit
        A_was_hit = true;

        if (unitA->unitOn->hp <= 0)
        {
            // Unit A died
            unitA->unitOn = nullptr;
            attackFinished = true;
            return;
        }
    }
}

void Attack::on_exit()
{
	gState.attackGui.attack_initiated = false;
    // Restore original colors
	if (unitA->unitOn)
		unitA->unitOn->an_sprite.sprite->setColor(sf::Color::White);
	if (unitB->unitOn)
		unitB->unitOn->an_sprite.sprite->setColor(sf::Color::White);
}

void Attack::update()
{
    // If attack is finished and flash is done, transition to next state
    if (attackFinished)
    {
        turnState->SetActionState(new ChooseTile(gState, turnState));
    }
}

void Attack::draw(state& gState)
{
    // Handle flash effect
	gState.attackGui.draw_units();

	if (first_time) {
        hitFlashClock = sf::Clock();
		clock2 = sf::Clock();
		first_time = false;
	}

    if (B_was_hit)
    {
        if (hitFlashClock.getElapsedTime().asSeconds() <= flashDuration)
        {
            unitA->unitOn->an_sprite.sprite_y = 2;
            unitA->unitOn->an_sprite.swap_interval = 0.1;
            unitB->unitOn->an_sprite.sprite->setColor(sf::Color::Red);
            return;
        }
        unitA->unitOn->an_sprite.sprite_y = 0;
        unitA->unitOn->an_sprite.swap_interval = 0.3;
        unitB->unitOn->an_sprite.sprite->setColor(sf::Color::White);
    }
    else// a missed
    {
        if (hitFlashClock.getElapsedTime().asSeconds() <= flashDuration)
        {
            unitA->unitOn->an_sprite.sprite_y = 2;
            unitA->unitOn->an_sprite.swap_interval = 0.1;
            unitB->unitOn->an_sprite.sprite->setColor(sf::Color{255, 255, 255, 150});
            return;
        }
        unitA->unitOn->an_sprite.sprite_y = 0;
        unitA->unitOn->an_sprite.swap_interval = 0.3;
		unitB->unitOn->an_sprite.sprite->setColor(sf::Color::White);
    }

    if (clock2.getElapsedTime().asSeconds() <= 1)
        return;

    if (first_time_b) {
        first_time_b = false;
        clock3 = sf::Clock();
        clock = sf::Clock();
    }

	if (A_was_hit)
	{
		if (clock.getElapsedTime().asSeconds() <= flashDuration)
		{
            unitB->unitOn->an_sprite.sprite_y = 2;
            unitB->unitOn->an_sprite.swap_interval = 0.1;
			unitA->unitOn->an_sprite.sprite->setColor(sf::Color::Red);
			return;
		}
        unitB->unitOn->an_sprite.sprite_y = 0;
        unitB->unitOn->an_sprite.swap_interval = 0.3;
		unitA->unitOn->an_sprite.sprite->setColor(sf::Color::White);
	}
	else// b missed
	{
		if (clock.getElapsedTime().asSeconds() <= flashDuration)
		{
            unitB->unitOn->an_sprite.sprite_y = 2;
            unitB->unitOn->an_sprite.swap_interval = 0.1;
			unitA->unitOn->an_sprite.sprite->setColor(sf::Color{ 255, 255, 255, 150 });
			return;
		}
        unitB->unitOn->an_sprite.sprite_y = 0;
        unitB->unitOn->an_sprite.swap_interval = 0.3;
		unitA->unitOn->an_sprite.sprite->setColor(sf::Color::White);
	}

    if (clock3.getElapsedTime().asSeconds() <= 1)
        return;

	attackFinished = true;
}