#pragma once
#include "turnState.hpp"
#include "MapLogic.h"

class EnemyTurn : public TurnState {
public:
    explicit EnemyTurn(MapLogic* map_logic);
    void on_enter() override;
    void on_exit() override;
    void update() override;
    void draw(state& gState) override;

private:
    MapLogic* map_logic;
};
