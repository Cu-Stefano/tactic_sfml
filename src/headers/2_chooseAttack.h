#pragma once
#include "actionState.hpp"

class Tile;
class state;

class ChooseAttack : public ActionState {
public:
	ChooseAttack(const state& state, const std::vector<Tile*>& tiles, Tile* tile);
	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(state& g_state) override;
};
