#pragma once

#include "actionState.hpp"

class Tile;
class PathAlgorithm;

class TileSelected : public ActionState {
	Tile* destination;
	PathAlgorithm* pathAlgorithm;
public:
	TileSelected(state& gState, TurnState* turnState, Tile* tile);
	void on_enter() override;
	void on_exit() override;
	void move_logic(Tile* tile, std::vector<Tile*> route);

	void update() override;
	void draw(state& gState) override;
};
