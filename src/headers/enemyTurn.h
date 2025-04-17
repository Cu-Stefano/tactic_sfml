#pragma once
#include "turnState.hpp"
#include "mapLogic.h"

class EnemyTurn : public TurnState {
public:
    explicit EnemyTurn(MapLogic* map_logic);
    void on_enter() override;
    void on_exit() override;
    void update() override;
    void draw(state& g_state) override;

private:
    MapLogic* map_logic;
};
