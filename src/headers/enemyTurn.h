#pragma once
#include "turnState.hpp"
#include "MapLogic.h"
#include "pathAlgorithm.h"
#include "tile.h"

class EnemyTurn : public TurnState {
    PathAlgorithm* pathAlgorithm;
public:
    explicit EnemyTurn(MapLogic* map_logic);
    void initialize_path_algorithm(Tile* unit);
    void HandleNoAllayToAttack(Tile* tile);
    void on_enter() override;
    void on_exit() override;
    void update() override;
    void draw(state& gState) override;

private:
    MapLogic* map_logic;
};
