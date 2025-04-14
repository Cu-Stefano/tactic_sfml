#pragma once

#include "actionState.hpp"

class TileSelected : public ActionState {
public:
	TileSelected(state& gs_state, TurnState* turnState);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw() override;
};
