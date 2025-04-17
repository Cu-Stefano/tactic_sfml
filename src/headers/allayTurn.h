#pragma once
#include "turnState.hpp"
#include "mapLogic.h"

class AllayTurn : public TurnState{
public:
    MapLogic* map_logic;
	explicit AllayTurn(MapLogic* map_logic);

    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;
    void update() override;
    void draw(::state& g_state) override;
};
