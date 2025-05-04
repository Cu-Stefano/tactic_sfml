#pragma once
#include "actionState.hpp"
#include "pathAlgorithm.h"

class ChooseTile : public ActionState {
	PathAlgorithm* enemyPathAllgorithm = nullptr;
public:
	ChooseTile(state& gState, TurnState* turnState);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(sf::RenderWindow& window) override;
};
