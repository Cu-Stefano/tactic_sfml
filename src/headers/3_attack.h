#pragma once
#include "actionState.hpp"

class Tile;
class state;

class Attack : public ActionState {
public:
	Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB, std::vector<int> aStats, std::vector<int> bStats);

	Tile* unitA;
	Tile* unitB;
	std::vector<int> aStats;
	std::vector<int> bStats;

	void on_enter() override;
	void on_exit() override;

	void update() override;
	void draw(state& gState) override;
};
