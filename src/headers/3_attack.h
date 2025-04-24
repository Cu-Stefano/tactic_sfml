#pragma once

#include "actionState.hpp"
#include <SFML/System/Clock.hpp>

class Tile;
class state;

class Attack : public ActionState {
public:
    Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB, std::vector<int> aStats, std::vector<int> bStats);

    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock clock3;

    Tile* unitA;
    Tile* unitB;
    std::vector<int> aStats;
    std::vector<int> bStats;

    // New members
    sf::Clock hitFlashClock;
    bool A_was_hit = false;
    bool B_was_hit = false;
    float flashDuration = 0.3f;
	bool first_time = true; 
	bool first_time_b = true; 

    bool attackFinished = false;          

    void on_enter() override;
    void on_exit() override;

    void update() override;
    void draw(state& gState) override;
};
