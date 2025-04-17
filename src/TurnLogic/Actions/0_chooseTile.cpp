#include "../../headers/0_chooseTile.h"
#include "../../headers/1_tileSelected.h"
#include "../../headers/state.hpp"
#include "../../headers/turnState.hpp"
#include "../../headers/tile.h"
#include "../../headers/unit.h"

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
		if (gs_state.isMouseOutOfRange(mousePos)) return;

		int tileX = static_cast<int>(mousePos.x) / 40;
		int tileY = static_cast<int>(mousePos.y) / 40;
		Tile* selectedTile = gs_state.Map[tileY][tileX];

	if (!selectedTile->shape.getGlobalBounds().contains(mousePos) || !selectedTile->UnitOn || !selectedTile->UnitOn->can_move)// sanity check
			return;

		startinPosition = { tileX, tileY };
		currentPosition = { tileX, tileY };

		//CHANGE STATE TO 1
		if (selectedTile->UnitOn != nullptr)
			turnState->SetActionState(new TileSelected(gs_state, turnState, selectedTile));
		//enemy case

   }
}

void ChooseTile::draw(state& gs_state)
{
	
}

