#pragma once

#include "actionState.hpp"

class Tile;
class PathAlgorithm;

class TileSelected : public ActionState {

	PathAlgorithm* pathAlgorithm;
	Tile* tile;
public:
	TileSelected(state& gsState, TurnState* turnState, Tile* tile);
	void on_enter() override;
	void on_exit() override;
	void move_Unit();

	void update() override;
	void draw(state& gsState) override;
};
