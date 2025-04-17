#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"
#include "../../headers/0_chooseTile.h"
#include "../../headers/2_chooseAttack.h"
#include "../../headers/state.hpp"
#include "../../headers/turnState.hpp"
#include "../../headers/tile.h"
#include "../../headers/unit.h"


TileSelected::TileSelected(state& gs_state, TurnState* turnState, Tile* tile)
	: ActionState(gs_state, turnState) {
	this->tile = tile;
	pathAlgorithm = new PathAlgorithm(tile, gs_state);
}

void TileSelected::on_enter() {
	pathAlgorithm->Execute();
	pathAlgorithm->Onode->UnitOn->an_sprite.swap_interval = 0.15f; // sec
	pathAlgorithm->Onode->UnitOn->an_sprite.sprite_y = 1;
}

void TileSelected::on_exit() {
	pathAlgorithm->ResetAll();
	delete pathAlgorithm;
	pathAlgorithm = nullptr;
}

void TileSelected::move_Unit()
{
	Vector2f mousePos = gs_state.window.mapPixelToCoords(Mouse::getPosition(gs_state.window));
	if (gs_state.isMouseOutOfRange(mousePos)) return;
	
	// If clicking on a nearby enemy
	if (isButtonPressed(Mouse::Button::Left))
	{
		auto hovered_tile = gs_state.getTileFromMousePosition(mousePos);
		if (!hovered_tile) return;
		if (std::find(pathAlgorithm->nearEnemies.begin(), pathAlgorithm->nearEnemies.end(), hovered_tile) != pathAlgorithm->nearEnemies.end())
		{
			turnState->SetActionState(new ChooseAttack(gs_state, pathAlgorithm->nearEnemies, hovered_tile));
			return;
		}

		// Exit conditions
		if (!hovered_tile || hovered_tile->UnitOn || std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), hovered_tile) == pathAlgorithm->path.end())
			return;

		currentPosition = gs_state.getCoordFromTile(hovered_tile);
		pathAlgorithm->Onode->move_unit(hovered_tile);

		//now hovered_tile is the new position of Onode
		hovered_tile->UnitOn->an_sprite.sprite_y = 0;
		hovered_tile->UnitOn->an_sprite.swap_interval = 0.3f; // sec
		
		//controllo i nighbours per vedere se ci sono nemici
		for (auto& neighbour : hovered_tile->Neighbours)
		{
			if (neighbour->UnitOn && neighbour->UnitOn->type == 1 - hovered_tile->UnitOn->type)
			{
				//turnState->SetActionState(new ChooseAttack(gs_state, turnState))
			}
		}
		turnState->SetActionState(new ChooseTile(gs_state, turnState));
	}
}

void TileSelected::update()
{
	for (auto& tile : pathAlgorithm->path)
	{
		tile->path_sprite->setColor(ALLAY_PATH_COLOR);
	}
	for (auto& tile : pathAlgorithm->attackBorderPath)
	{
		tile->path_sprite->setColor(ALLAY_ATTACK_COLOR);
	}
	for (auto tile : pathAlgorithm->attackList)
	{
		tile->path_sprite->setColor(ALLAY_ATTACK_COLOR);
	}
	for (auto tile : pathAlgorithm->nearEnemies)
	{
		tile->path_sprite->setColor(ALLAY_ATTACK_COLOR);
	}

	//mouse actions:
	Vector2f mousePos = gs_state.window.mapPixelToCoords(Mouse::getPosition(gs_state.window));
	auto hovered_tile = gs_state.getTileFromMousePosition(mousePos);
	if (!hovered_tile) return;

	if (hovered_tile->UnitOn && hovered_tile->UnitOn->type == 1 - pathAlgorithm->Onode->UnitOn->type)
	{
		hovered_tile->shape.setOutlineThickness(-2);
		hovered_tile->shape.setOutlineColor(Color::Red);
	}

	//hover::Trail
    if (std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), hovered_tile) != pathAlgorithm->path.end()) {
		auto currNode = hovered_tile;
		while (currNode != pathAlgorithm->Onode)
		{
			currNode->shape.setOutlineThickness(-2);
			currNode->shape.setOutlineColor(Color::Blue);
			currNode = currNode->Parent;
		}
		//left_mouse::Move
		move_Unit();
    }

	//right_mouse::Back
	if (Mouse::isButtonPressed(Mouse::Button::Right))
	{
		pathAlgorithm->Onode->UnitOn->an_sprite.sprite_y = 0;
		pathAlgorithm->Onode->UnitOn->an_sprite.swap_interval = 0.3f; // sec
		turnState->SetActionState(new ChooseTile(gs_state, turnState));
	}
		

}

void TileSelected::draw(state& gs_state)
{
	for (auto& tile : pathAlgorithm->path)
	{
		gs_state.window.draw(*tile->path_sprite);
	}
	for (auto& tilea : pathAlgorithm->attackBorderPath)
	{
		gs_state.window.draw(*tilea->path_sprite);
	}
	for (auto tile : pathAlgorithm->attackList)
	{
		gs_state.window.draw(*tile->path_sprite);
	}
	for (auto tile : pathAlgorithm->nearEnemies)
	{
		gs_state.window.draw(*tile->path_sprite);
	}
}


