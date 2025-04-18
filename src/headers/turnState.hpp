#pragma once
class state;
class ActionState;

class TurnState {
public:
    TurnState(state& gsState) : gsState(gsState), CurrentActionState(nullptr){}

    state& gsState;

    ActionState* CurrentActionState;

	virtual void on_enter() = 0;
	virtual void on_exit() = 0;
    virtual void SetActionState(ActionState* action);

    virtual void update() = 0;
    virtual void draw(state& gState) = 0;

};

