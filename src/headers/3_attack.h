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
    bool remove_dead_unit(Tile* unit);
    void draw(sf::RenderWindow& window) override;

    bool attackFinished = false;
    int CritA = false;
    int CritB = false;
    

private:
    enum class AttackPhase {
        FirstAttack,
        SecondAttack,
        Dead,
        Finished,
    	DoubleAttack
    };

    void handle_attack(Tile* target, Tile* attacker, const std::vector<int>& attackerStats, std::vector<int>& targetStats, bool& wasHit);
	void handle_phase(Unit* attacker, Tile* target, bool wasHit, float delay, AttackPhase nextPhase, sf::Clock currclock, bool crit);

    Tile* unitA;
    Tile* unitB;
    std::vector<int> aStats;
    std::vector<int> bStats;

    AttackPhase currentPhase = AttackPhase::FirstAttack;

    bool A_was_hit = false;
    bool B_was_hit = false;

    Tile* dead;

    sf::Clock clock2;
    sf::Clock clock3;
    sf::Clock clock1;

    bool first_time = true;
    bool first_time_b = true;
    bool first_time_d = true;

    const float flash_duration_ = 0.3f;
    const float delay_ = 0.9f;
};