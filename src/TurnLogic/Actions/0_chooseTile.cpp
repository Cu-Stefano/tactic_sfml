#include "../../headers/0_chooseTile.h"

#include <iostream>

#include "../../headers/1_tileSelected.h"
#include "../../headers/state.h"
#include "../../headers/tile.h"

ChooseTile::ChooseTile(state& gs_state, TurnState* turnState)
    : ActionState(gs_state, turnState) {
}

void ChooseTile::on_enter() {

}

void ChooseTile::on_exit() {
    // Clean up logic
}

void ChooseTile::update()
{
	if ( Mouse::isButtonPressed(Mouse::Button::Left) )
	{
		Vector2f mousePos = gs_state.window.mapPixelToCoords(Mouse::getPosition(gs_state.window));
		if (mousePos.x > gs_state.menubar_attack_window_x || mousePos.y > gs_state.menubar_attack_y) return;

		int tileX = static_cast<int>(mousePos.x) / 40;
		int tileY = static_cast<int>(mousePos.y) / 40;
		Tile selectedTile = gs_state.Map[tileY][tileX];

		if (!selectedTile.shape.getGlobalBounds().contains(mousePos))// sanity check
			return;

		std::cout << tileX << " " << tileY << std::endl;

		startinPosition = { tileX, tileY };
		currentPosition = { tileX, tileY };

		//CHANGE STATE TO 1
		turnState->SetActionState(new TileSelected(gs_state, turnState));

		//enemy case

	   
   }
}

void ChooseTile::draw() {
    // Draw logic
}
