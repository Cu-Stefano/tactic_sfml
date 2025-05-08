#pragma once
#include "3_attack.h"
#include "turnState.hpp"
#include "pathAlgorithm.h"
#include "tile.h"

class EnemyTurn : public TurnState {
public:
    enum class turn_fase {
        TURN_NAME,
    	CHOOSE_ACTION,           
        MOVE,
        SHOW_ATTACK_GUI,
    	SHOW_PATH,
        ATTACK,
        END
    };

    explicit EnemyTurn(state& gs);

    void on_enter() override;
    void on_exit() override;

    void initialize_path_algorithm(Tile* unit);
    void end_enemy_turn(Tile* tile);
    Tile* get_next_enemy();
    Tile* find_tile_to_land(Tile* attackedUnit) const;

    void move_towards_allay();
    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    PathAlgorithm* pathAlgorithm;
    turn_fase current_phase = turn_fase::TURN_NAME;
	Tile* current_enemy = nullptr;
	Tile* tileToLand = nullptr;
	Tile* allayToAttack = nullptr;

    std::vector<Tile*>::iterator curr_enemy_iter;

	sf::Clock showAttackGuiClock = sf::Clock();
	sf::Clock clock = sf::Clock();
    bool previewSelected = false;
    std::vector<Tile*> route{};
    Attack* attackState = nullptr;
    int curr_enemy_index;
};
