#include "../../headers/3_attack.h"
#include "../../headers/tile.h"
#include "../../headers/actionState.hpp"
#include "../../headers/0_chooseTile.h"
#include "../../headers/turnState.hpp"
#include "../../headers/enemyTurn.h"
#include "../../headers/unit.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include "../../headers/mapBuilder.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

Attack::Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB,
               std::vector<int> aStats, std::vector<int> bStats)
	: ActionState(state, turnState), unitA(unitA), unitB(unitB),
	  aStats(aStats), bStats(bStats), dead(nullptr)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Attack::handle_attack(Tile* target, const std::vector<int>& attackerStats, std::vector<int>& targetStats, bool& wasHit)
{
    if (rand() % 100 < attackerStats[2]) // Hit chance 
    {
        int damage = attackerStats[1];
        if (rand() % 100 < attackerStats[3]) // Crit chance 
        {
            wasCrit = true;
            damage *= 3;
        }

        targetStats[0] -= damage;
        wasHit = true;
        target->unitOn->hp = std::max(0, targetStats[0]);
    }
}

void Attack::handle_phase(Unit* attacker, Tile* target, bool wasHit, float delay, AttackPhase nextPhase, sf::Clock currclock)
{
    if (currclock.getElapsedTime().asSeconds() <= flash_duration_) {
        if (wasCrit)
            attacker->an_sprite.sprite->setColor(sf::Color(255, 255, 0, 230));
        else
            attacker->an_sprite.sprite->setColor(sf::Color::White);

        attacker->an_sprite.sprite_y = 2;
		attacker->an_sprite.swap_interval = 0.1; // sec
        if (target) {
            target->unitOn->an_sprite.sprite->setColor(wasHit ? sf::Color::Red : sf::Color(255, 255, 255, 150));
        }
    }
    else if (currclock.getElapsedTime().asSeconds() <= flash_duration_ + delay) {
        attacker->an_sprite.sprite->setColor(sf::Color::White);
        attacker->an_sprite.sprite_y = 0;
        attacker->an_sprite.swap_interval = SWAP_INTERVAL;
        if (target) {
            target->unitOn->an_sprite.sprite->setColor(sf::Color::White);
        }
    }
    else {
        if (!target || target->unitOn->hp == 0)
        {
            dead = target;
            first_time_b = true;
        	currentPhase = AttackPhase::Dead;
        }
        else 
            currentPhase = nextPhase;
    }
}

void Attack::on_enter()
{
    gState.attackGui.attack_initiated = true;

    handle_attack(unitB, aStats, bStats, B_was_hit);
    if (unitB->unitOn)
        handle_attack(unitA, bStats, aStats, A_was_hit);
}

void Attack::on_exit()
{
    gState.attackGui.attack_initiated = false;
}

void Attack::update()
{
    if (attackFinished)
    {
        if (unitA->unitOn)
        {
            unitA->unitOn->has_moved();
            unitA->unitOn->canMove = false;
            unitA->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
        }

        if (!gState.check_all_units_moved(0))
            turnState->SetActionState(new ChooseTile(gState, turnState));
        else gState.MapLogic.set_state(new EnemyTurn(gState));
    }
}

bool Attack::remove_dead_unit(Tile* unit)
{
	if (!unit->unitOn || unit->unitOn->hp == 0)
	{
		if (unit->unitOn->type == 1)
		{
			enemy_list.erase(std::remove(enemy_list.begin(), enemy_list.end(), unit->unitOn), enemy_list.end());
			enemy_tile_list.erase(std::remove(enemy_tile_list.begin(), enemy_tile_list.end(), unit), enemy_tile_list.end());
		}
        else
        {
            allay_list.erase(std::remove(allay_list.begin(), allay_list.end(), unit->unitOn), allay_list.end());
            allay_tile_list.erase(std::remove(allay_tile_list.begin(), allay_tile_list.end(), unit), allay_tile_list.end());
        }

		delete unit->unitOn;
        unit->unitOn = nullptr;
        unit->passable = true;
        unit->walkable = true;

		return true;
	}
	return false;
}

void Attack::draw(sf::RenderWindow& window)
{
    switch (currentPhase) {

    case AttackPhase::FirstAttack:

        if (first_time)
        {
            clock1 = sf::Clock();
            clock2 = sf::Clock();
            first_time = false;
            unitA->unitOn->an_sprite.curr_frame = 3;
        }
        handle_phase(unitA->unitOn, unitB, B_was_hit, delay_, AttackPhase::SecondAttack, clock1);
        break;

    case AttackPhase::SecondAttack:
        
        if (clock2.getElapsedTime().asSeconds() <= 1)
            return;

        if (first_time_b)
        {
            clock1 = sf::Clock();
            clock3 = sf::Clock();
            first_time_b = false;
            unitB->unitOn->an_sprite.curr_frame = 3;
        }
        handle_phase(unitB->unitOn, unitA, A_was_hit, delay_, AttackPhase::Finished, clock1);
        break;

    case AttackPhase::Dead:

        if (dead->unitOn && dead->unitOn->hp == 0)
        {
            if (first_time_b)
			{
				first_time_b = false;
                dead->unitOn->an_sprite.clock.restart();
                dead->unitOn->an_sprite.curr_frame = 3;
			}
        	if (clock3.getElapsedTime().asSeconds() <= 2.0f)  
        	{
                dead->unitOn->an_sprite.sprite_y = 3;
                dead->unitOn->an_sprite.swap_interval = 0.15;
        	}
	        else
	        {
                remove_dead_unit(dead);
                currentPhase = AttackPhase::Finished;
	        }
        }

        break;

    case AttackPhase::Finished:

        if (clock3.getElapsedTime().asSeconds() <= 1)
            return;

        attackFinished = true;
        break;
    }

    gState.attackGui.draw_units();
}


