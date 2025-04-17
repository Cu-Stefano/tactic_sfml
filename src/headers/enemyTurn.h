#pragma once
#include "turnState.hpp"
class MapLogic;

class EnemyTurn : public TurnState {
public:
    MapLogic* map_logic;
    explicit EnemyTurn(MapLogic* map_logic);

    void on_enter() override;
    void on_exit() override;
    void update() override;
    void draw(::state& g_state) override;
};
