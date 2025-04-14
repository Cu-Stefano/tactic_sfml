#pragma once

#include "actionState.hpp"

class ChooseTile : public ActionState {
public:
	ChooseTile(state& gs_state, TurnState* turnState);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw() override;
};
