#include "../../headers/0_chooseTile.h"
#include "../../headers/1_tileSelected.h"

#include <iostream>

#include "../../headers/state.h"
#include "../../headers/tile.h"

TileSelected::TileSelected(state& gs_state, TurnState* turnState)
	: ActionState(gs_state, turnState) {
}

void TileSelected::on_enter() {
	std::cout << "TileSelected::on_enter()" << std::endl;
}

void TileSelected::on_exit() {
	// Clean up logic
}

void TileSelected::update()
{
}

void TileSelected::draw() {
	// Draw logic
}
