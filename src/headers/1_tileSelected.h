#pragma once

#include "actionState.hpp"

class Tile;
class PathAlgorithm;

class TileSelected : public ActionState {

	PathAlgorithm* pathAlgorithm;
	Tile* tile;
public:
	TileSelected(state& gs_state, TurnState* turnState, Tile* tile);
	void on_enter() override;
	void on_exit() override;
	void move_Unit();

	void update() override;
	void draw(state& gs_state) override;
};
