#pragma once

class state;

class TurnState {
public:
    TurnState(state& gs_state) : gs_state(gs_state) {}
    state& gs_state;
	virtual void on_enter() = 0;
	virtual void on_exit() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

};
