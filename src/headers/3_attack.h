#pragma once

#include "actionState.hpp"

class Attack : public ActionState {
public:
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw() override;
};
