#pragma once
#include "actionState.hpp"

class ChooseTile : public ActionState {
public:
	ChooseTile(state& gsState, TurnState* turnState);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(state& gsState) override;
};
