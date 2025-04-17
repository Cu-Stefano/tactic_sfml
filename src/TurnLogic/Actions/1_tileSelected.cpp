#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"

#include <iostream>

#include "../../headers/0_chooseTile.h"


TileSelected::TileSelected(state& gs_state, TurnState* turnState, Tile* tile)
	: ActionState(gs_state, turnState) {
	this->tile = tile;
	pathAlgorithm = new PathAlgorithm(tile, gs_state);
}

void TileSelected::on_enter() {
	std::cout << "TileSelected::on_enter()" << std::endl;
	pathAlgorithm->Execute();
	//pathAlgorithm->Onode->UnitOn->set_state(new MoveState(pathAlgorithm->Onode->UnitOn));
}

void TileSelected::on_exit() {
	pathAlgorithm->ResetAll();
	delete pathAlgorithm;
	pathAlgorithm = nullptr;
}

void TileSelected::move_Unit()
{
	
	

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
	if (mousePos.x > gs_state.menubar_attack_window_x || mousePos.y > gs_state.menubar_attack_y || mousePos.x < 0 || mousePos.y < 0) return;
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


