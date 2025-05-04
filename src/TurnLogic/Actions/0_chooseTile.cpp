#include "../../headers/0_chooseTile.h"
#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"
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
	if (enemyPathAllgorithm)
		enemyPathAllgorithm->reset_all();
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

		if (selectedTile->unitOn != nullptr)
		{
			if (selectedTile->unitOn->type == 0)
				turnState->SetActionState(new TileSelected(gState, turnState, selectedTile));
			else
			{
				enemyPathAllgorithm = new PathAlgorithm(selectedTile, gState);
				enemyPathAllgorithm->execute();
				enemyPathAllgorithm->update();
			}
		}
	}
	else 
		if (Mouse::isButtonPressed(Mouse::Button::Right) && enemyPathAllgorithm)
		{
			enemyPathAllgorithm->reset_all();
			delete enemyPathAllgorithm;
			enemyPathAllgorithm = nullptr;
		}
			
}

void ChooseTile::draw(sf::RenderWindow& window)
{
	if (enemyPathAllgorithm)
	{
		for (auto& tile : enemyPathAllgorithm->path)
			gState.window.draw(tile->path_sprite);

		for (auto& tile : enemyPathAllgorithm->attackBorderPath)
			gState.window.draw(tile->path_sprite);

		for (auto tile : enemyPathAllgorithm->attackList)
			gState.window.draw(tile->path_sprite);

		for (auto tile : enemyPathAllgorithm->nearEnemies)
			gState.window.draw(tile->path_sprite);
	}
}

