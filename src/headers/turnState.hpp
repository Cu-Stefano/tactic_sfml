#pragma once

class state;
class ActionState;

class TurnState {
public:
    TurnState(state& gs_state) : gs_state(gs_state), CurrentActionState(nullptr)
    {
    }

    state& gs_state;

    ActionState* CurrentActionState;

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;
    virtual void SetActionState(ActionState* action);

    virtual void update() = 0;
    virtual void draw() = 0;

};

