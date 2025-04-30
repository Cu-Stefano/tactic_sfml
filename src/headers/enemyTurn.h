#pragma once
#include "turnState.hpp"
#include "MapLogic.h"
#include "pathAlgorithm.h"
#include "tile.h"

class EnemyTurn : public TurnState {
public:
    enum class turn_fase {
        IDLE,           // idle
        PROCESSING_TURN, // an enemy is choosing what to do
        SHOW_ATTACK_GUI,
        END,
    	SHOW_PATH
    };

    explicit EnemyTurn(MapLogic* map_logic);
    void initialize_path_algorithm(Tile* unit);
    void end_enemy_turn(Tile* tile);
    void attack_allay(Tile* tile);
    void on_enter() override;
    void on_exit() override;
    Tile* get_next_enemy();
    void update() override;
    void draw(state& gState) override;

private:
    MapLogic* map_logic;
    PathAlgorithm* pathAlgorithm;
    turn_fase current_phase = turn_fase::IDLE;
	Tile* current_enemy = nullptr;

    std::vector<Tile*>::iterator iter;

	sf::Clock showAttackGuiClock = sf::Clock();
	sf::Clock showPathClock = sf::Clock();

};
