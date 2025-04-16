#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"

#include <iostream>


TileSelected::TileSelected(state& gs_state, TurnState* turnState, Tile* tile)
	: ActionState(gs_state, turnState) {
	this->tile = tile;
	pathAlgorithm = new PathAlgorithm(tile, gs_state);
}

void TileSelected::on_enter() {
	std::cout << "TileSelected::on_enter()" << std::endl;
	pathAlgorithm->Execute();
}

void TileSelected::on_exit() {
	// Clean up logic
}

void TileSelected::update()
{
	for (auto tile : pathAlgorithm->path)
	{
		tile->sprite.setColor(ALLAY_PATH_COLOR);
	}

	
}

void TileSelected::draw() {
	// Draw logic
}
