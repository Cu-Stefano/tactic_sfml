#pragma once
class MapLogic;
class TurnState;

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
