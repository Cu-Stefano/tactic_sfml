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

Attack::Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB,
               std::vector<int> aStats, std::vector<int> bStats)
    : ActionState(state, turnState), unitA(unitA), unitB(unitB),
    aStats(aStats), bStats(bStats)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
	clockfirst = sf::Clock();
}

void Attack::handleAttack(Tile* target, const std::vector<int>& attackerStats, std::vector<int>& targetStats, bool& wasHit)
{
    if (rand() % 100 < attackerStats[2]) // Hit chance 
    {
        int damage = attackerStats[1];
        if (rand() % 100 < attackerStats[3]) // Crit chance 
        {
            damage *= 3;
        }

        targetStats[0] -= damage;
        wasHit = true;
        target->unitOn->hp = std::max(0, targetStats[0]);

        if (target->unitOn->hp == 0)
        {
            if (target->unitOn->type == 1)
                enemy_list.erase(std::remove(enemy_list.begin(), enemy_list.end(), target->unitOn), enemy_list.end());
            else
                allay_list.erase(std::remove(allay_list.begin(), allay_list.end(), target->unitOn), allay_list.end());

            delete target->unitOn;
            target->unitOn = nullptr;
            target->passable = true;
			target->walkable = true;
        }
    }
}

void Attack::handlePhase(Unit* attacker, Unit* target, bool wasHit, float delay, AttackPhase nextPhase, sf::Clock currclock)
{
    if (currclock.getElapsedTime().asSeconds() <= flashDuration) {
		std::cout << attacker->an_sprite.curr_frame << std::endl;
        attacker->an_sprite.sprite_y = 2;
		attacker->an_sprite.swap_interval = 0.15; // sec
        if (target) {
            target->an_sprite.sprite->setColor(wasHit ? sf::Color::Red : sf::Color(255, 255, 255, 150));
        }
    }
    else if (currclock.getElapsedTime().asSeconds() <= flashDuration + delay) {
        attacker->an_sprite.sprite_y = 0;
        attacker->an_sprite.swap_interval = SWAP_INTERVAL;
        if (target) {
            target->an_sprite.sprite->setColor(sf::Color::White);
        }
    }
    else {
        currentPhase = nextPhase;
    }
}

void Attack::on_enter()
{
    gState.attackGui.attack_initiated = true;
    attackClock.restart();

    handleAttack(unitB, aStats, bStats, B_was_hit);
    if (unitB->unitOn)
        handleAttack(unitA, bStats, aStats, A_was_hit);
}

void Attack::on_exit()
{
    gState.attackGui.attack_initiated = false;
    if (unitA)
    {
	    unitA->unitOn->has_moved();
		unitA->unitOn->canMove = false;
        unitA->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
    }
}

void Attack::update()
{
    gState.attackGui.unitA->update();
    gState.attackGui.unitB->update();

    if (attackFinished)
        turnState->SetActionState(new ChooseTile(gState, turnState));
}

void Attack::draw(state& gState)
{
    gState.attackGui.draw_units();

    switch (currentPhase) {
    case AttackPhase::FirstAttack:
        if (first_time)
        {
            hitFlashClock = sf::Clock();
            clock2 = sf::Clock();
            first_time = false;
			gState.attackGui.unitA->an_sprite.curr_frame = 0;
        }
        handlePhase(gState.attackGui.unitA, gState.attackGui.unitB, B_was_hit, attackDelay, AttackPhase::SecondAttack, hitFlashClock);
        break;
    case AttackPhase::SecondAttack:
        if (clock2.getElapsedTime().asSeconds() <= 1)
            return;
		if (first_time_b)
		{
			clock = sf::Clock();
			clock3 = sf::Clock();
            first_time_b = false;
			gState.attackGui.unitB->an_sprite.curr_frame = 0;
		}
        handlePhase(gState.attackGui.unitB, gState.attackGui.unitA, A_was_hit, counterDelay, AttackPhase::Finished, clock);
        break;
    case AttackPhase::Finished:
        if (clock3.getElapsedTime().asSeconds() <= 1)
            return;
        attackFinished = true;
        /*turnState->SetActionState(new ChooseTile(gState, turnState));*/
        break;
    }
}