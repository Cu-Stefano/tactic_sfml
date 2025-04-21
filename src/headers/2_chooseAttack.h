#pragma once
#include "actionState.hpp"

class Tile;
class state;

class ChooseAttack : public ActionState {
	std::vector<Tile*> enemyNear;
	Tile* attackingUnit;
	bool preview_selected = false;
public:
	ChooseAttack(state& state, const std::vector<Tile*>& enemyNear, Tile* attackingUnit);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(state& gsState) override;
};
