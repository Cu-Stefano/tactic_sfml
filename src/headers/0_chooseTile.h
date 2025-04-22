#pragma once
#include "actionState.hpp"

class ChooseTile : public ActionState {
public:
	ChooseTile(state& gState, TurnState* turnState);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(state& gState) override;
};
