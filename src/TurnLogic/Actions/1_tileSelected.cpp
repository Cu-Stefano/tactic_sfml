#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"

#include <iostream>

#include "../../headers/0_chooseTile.h"
#include "../../headers/2_chooseAttack.h"


TileSelected::TileSelected(state& gs_state, TurnState* turnState, Tile* tile)
	: ActionState(gs_state, turnState) {
	this->tile = tile;
	pathAlgorithm = new PathAlgorithm(tile, gs_state);
}

void TileSelected::on_enter() {
	pathAlgorithm->Execute();
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

		turnState->SetActionState(new ChooseTile(gs_state, turnState));
		////controllo i nighbours per vedere se ci sono nemici
		//// If there is an enemy unit in attack range, change state
		//if (!newPathAlgorithm->nearEnemies.empty())
		//{
		//	turnState->SetActionState(new ChooseAttack(gs_state, newPathAlgorithm->nearEnemies, butt));
		//}
		//else
		//{
		//	// Unit can't move anymore
		//	_startinPosition = { 0, 0 };
		//	_currentPosition = { 0, 0 };

		//	gs_state.maplogic.UnitCantMoveNoMore(butt);

		//	// If all ally units have moved, change state to enemy turn
		//	if (std::all_of(MapBuilder::AllayButtonList.begin(), MapBuilder::AllayButtonList.end(),
		//		[](Button* allay) { return !(allay->getTile()->UnitOn->CanMove); }))
		//	{
		//		turnState->SetActionState(new EnemyTurn(gs_state.maplogic));
		//	}

		//	// Change state back to TileToBeSelected
		//	turnState->SetActionState(new TileToBeSelected(gs_state));
		//}
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
	if (gs_state.isMouseOutOfRange(mousePos)) return;
	auto hovered_tile = gs_state.getTileFromMousePosition(mousePos);
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
		turnState->SetActionState(new ChooseTile(gs_state, turnState));

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


