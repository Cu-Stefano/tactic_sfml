#pragma once

#include "actionState.hpp"
#include <SFML/System/Clock.hpp>

#include "unit.h"

class Tile;
class state;

class Attack : public ActionState {
public:
    Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB,
        std::vector<int> aStats, std::vector<int> bStats);

    void on_enter() override;
    void on_exit() override;
    void update() override;
    void draw(state& gState) override;

private:
    enum class AttackPhase {
        FirstAttack,
        SecondAttack,
        Finished
    };

    void handleAttack(Tile* target, const std::vector<int>& attackerStats, std::vector<int>& targetStats, bool& wasHit);
	void handlePhase(Unit* attacker, Unit* target, bool wasHit, float delay, AttackPhase nextPhase, sf::Clock currclock);
    Tile* unitA;
    Tile* unitB;
    std::vector<int> aStats;
    std::vector<int> bStats;

    sf::Clock attackClock;
    AttackPhase currentPhase = AttackPhase::FirstAttack;

    bool A_was_hit = false;
    bool B_was_hit = false;


    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock clock3;
    sf::Clock hitFlashClock;
    bool first_time = true;
    bool first_time_b = true;
    bool attackFinished = false;


    const float flashDuration = 0.3f;
    const float attackDelay = 0.9f;
    const float counterDelay = 0.9f;
};