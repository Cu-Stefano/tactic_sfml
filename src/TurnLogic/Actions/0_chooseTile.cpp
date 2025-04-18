#include "../../headers/0_chooseTile.h"
#include "../../headers/1_tileSelected.h"
#include "../../headers/state.hpp"
#include "../../headers/turnState.hpp"
#include "../../headers/tile.h"
#include "../../headers/unit.h"

ChooseTile::ChooseTile(state& gsState, TurnState* turnState)
    : ActionState(gsState, turnState) {
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
		Vector2f mousePos = gsState.window.mapPixelToCoords(Mouse::getPosition(gsState.window));
		if (gsState.isMouseOutOfRange(mousePos)) return;

		int tileX = static_cast<int>(mousePos.x) / 40;
		int tileY = static_cast<int>(mousePos.y) / 40;
		Tile* selectedTile = gsState.map[tileY][tileX];

	if (!selectedTile->shape.getGlobalBounds().contains(mousePos) || !selectedTile->unitOn || !selectedTile->unitOn->can_move)// sanity check
			return;

		startinPosition = { tileX, tileY };
		currentPosition = { tileX, tileY };

		//CHANGE STATE TO 1
		if (selectedTile->unitOn != nullptr)
			turnState->SetActionState(new TileSelected(gsState, turnState, selectedTile));
		//enemy case

   }
}

void ChooseTile::draw(state& gsState)
{
	
}

