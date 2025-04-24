#include "../../headers/0_chooseTile.h"
#include "../../headers/1_tileSelected.h"
#include "../../headers/state.hpp"
#include "../../headers/turnState.hpp"
#include "../../headers/tile.h"
#include "../../headers/unit.h"
using namespace sf;

ChooseTile::ChooseTile(state& gState, TurnState* turnState)
    : ActionState(gState, turnState) {
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
		Vector2f mousePos = gState.window.mapPixelToCoords(Mouse::getPosition(gState.window));
		if (gState.isMouseOutOfRange(mousePos)) return;

		int tileX = static_cast<int>(mousePos.x) / 40;
		int tileY = static_cast<int>(mousePos.y) / 40;
		if (tileX < 0 || tileX >= WINDOW_WIDTH / 40 || tileY < 0 || tileY >= WINDOW_HEIGHT / 40)
			return;
		Tile* selectedTile = gState.map[tileY][tileX];

	if (!selectedTile->shape.getGlobalBounds().contains(mousePos) || !selectedTile->unitOn || !selectedTile->unitOn->canMove)// sanity check
			return;

		startinPosition = { tileX, tileY };
		currentPosition = { tileX, tileY };

		//CHANGE STATE TO 1
		if (selectedTile->unitOn != nullptr)
			turnState->SetActionState(new TileSelected(gState, turnState, selectedTile));
		//enemy case

   }
}

void ChooseTile::draw(state& gState)
{
	
}

