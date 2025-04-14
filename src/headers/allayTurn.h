#pragma once
#include "turnState.hpp"
class MapLogic;

class AllayTurn : public TurnState{
public:
    MapLogic* map_logic;
	explicit AllayTurn(MapLogic* map_logic);

    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;
    void update() override;
    void draw() override;
};
