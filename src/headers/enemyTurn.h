#pragma once
#include "3_attack.h"
#include "turnState.hpp"
#include "MapLogic.h"
#include "pathAlgorithm.h"
#include "tile.h"

class EnemyTurn : public TurnState {
public:
    enum class turn_fase {
        TURN_NAME,
    	IDLE,           
        PROCESSING_TURN,
        SHOW_ATTACK_GUI,
    	SHOW_PATH,
        ATTACK,
        END
    };

    explicit EnemyTurn(MapLogic* map_logic);

    void on_enter() override;
    void on_exit() override;

    void initialize_path_algorithm(Tile* unit);
    void end_enemy_turn(Tile* tile);
    void attack_allay(Tile* tile);
    Tile* get_next_enemy();
    Tile* find_tile_to_land(Tile* attackedUnit);

    void move_towards_allay();
    void update() override;
    void draw(state& gState) override;

private:
    MapLogic* map_logic;
    PathAlgorithm* pathAlgorithm;
    turn_fase current_phase = turn_fase::TURN_NAME;
	Tile* current_enemy = nullptr;
	Tile* tileToLand = nullptr;
	Tile* allayToAttack = nullptr;

    std::vector<Tile*>::iterator iter;

	sf::Clock showAttackGuiClock = sf::Clock();
	sf::Clock clock = sf::Clock();
    bool previewSelected = false;
    std::vector<Tile*> route{};
    Attack* attackState = nullptr;
};
