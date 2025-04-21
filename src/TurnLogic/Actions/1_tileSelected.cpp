#include "../../headers/1_tileSelected.h"
#include "../../headers/pathAlgorithm.h"
#include "../../headers/0_chooseTile.h"
#include "../../headers/2_chooseAttack.h"
#include "../../headers/enemyTurn.h"
#include "../../headers/state.hpp"
#include "../../headers/turnState.hpp"
#include "../../headers/tile.h"
#include "../../headers/unit.h"

#include <iostream>
#include <algorithm>

using namespace sf;

int c;// contatore usato per saltare il primo click che viene registrato per sbaglio dallo stato precedente:chooseTile
bool wasButtonPressed;
Tile* destination;

TileSelected::TileSelected(state& gsState, TurnState* turnState, Tile* tile)
	: ActionState(gsState, turnState) {
	pathAlgorithm = new PathAlgorithm(tile, gsState);
}

void TileSelected::on_enter() {
	wasButtonPressed = false;
	c = 0;
	pathAlgorithm->execute();
	if (!pathAlgorithm->Onode->unitOn->isMoving)
	{
		pathAlgorithm->Onode->unitOn->an_sprite.swap_interval = SWAP_INTERVAL_RUN;
		pathAlgorithm->Onode->unitOn->an_sprite.sprite_y = 1;
	}
}

void TileSelected::on_exit() {
	pathAlgorithm->reset_all();
	delete pathAlgorithm;
	pathAlgorithm = nullptr;
}

void TileSelected::move_logic(Tile* hovered_tile, vector<Tile*> route)
{
	Vector2f mousePos = gsState.window.mapPixelToCoords(Mouse::getPosition(gsState.window));
	if (gsState.isMouseOutOfRange(mousePos)) return;

	if (Mouse::isButtonPressed(Mouse::Button::Left) && !Unit::IsAnyUnitMoving)
	{
		if (!wasButtonPressed)//entra al primo click e poi di nuovo soltanto quando si rilascia left mouse
		{
			wasButtonPressed = true;
			if (hovered_tile == pathAlgorithm->Onode)
			{
				c++;
				if (c < 2) return;
			}
			else
			{
				// Exit conditions
				if (!hovered_tile || hovered_tile->unitOn || std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), hovered_tile) == pathAlgorithm->path.end())
					return;
			}

			currentPosition = gsState.getCoordFromTile(hovered_tile);
			//now hovered_tile is the new position of Onode
			destination = hovered_tile;
			pathAlgorithm->Onode->move_unit(hovered_tile, route);
		}
	}
	else
	{
		wasButtonPressed = false; // Resetto lo stato quando il pulsante viene rilasciato
	}
}


void TileSelected::update()
{
	for (auto& tile : pathAlgorithm->path)
	{
		tile->path_sprite.setColor(ALLAY_PATH_COLOR);
	}
	for (auto& tile : pathAlgorithm->attackBorderPath)
	{
		tile->path_sprite.setColor(ALLAY_ATTACK_COLOR);
	}
	for (auto tile : pathAlgorithm->attackList)
	{
		tile->path_sprite.setColor(ALLAY_ATTACK_COLOR);
	}
	for (auto tile : pathAlgorithm->nearEnemies)
	{
		tile->path_sprite.setColor(ALLAY_ATTACK_COLOR);
	}

	//mouse actions:
	Vector2f mousePos = gsState.window.mapPixelToCoords(Mouse::getPosition(gsState.window));
	auto hovered_tile = gsState.get_tile_from_mouse_position(mousePos);
	if (!hovered_tile) return;

	//hover::Trail
    if (std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), hovered_tile) != pathAlgorithm->path.end() || hovered_tile == pathAlgorithm->Onode) {
		auto currNode = hovered_tile;
		std::vector<Tile*> route{};
		while (currNode != pathAlgorithm->Onode)
		{
			route.push_back(currNode);
			currNode->shape.setOutlineThickness(-2);
			currNode->shape.setOutlineColor(Color::Blue);
			currNode = currNode->Parent;
		}
    	move_logic(hovered_tile, route);
    }

	if (!Unit::IsAnyUnitMoving && Unit::hasSomeActionBeenStared)
	{
		//controllo i nighbours per vedere se ci sono nemici
		std::vector<Tile*> near_enemies{};
		for (auto& neighbour : destination->neighbours)
		{
			if (neighbour->unitOn && neighbour->unitOn->type == 1 - destination->unitOn->type)
			{
				near_enemies.push_back(neighbour);
			}
		}
		if (!near_enemies.empty())
			turnState->SetActionState(new ChooseAttack(gsState, near_enemies, destination));
		else
		{
			bool allAlliesCannotMove = std::all_of(allay_list.begin(), allay_list.end(), [](Unit* unit) {
				return !unit->canMove;
				});

			if (allAlliesCannotMove) {
				gsState.MapLogic.set_state(new EnemyTurn(&gsState.MapLogic));
			}
			else
				turnState->SetActionState(new ChooseTile(gsState, turnState));
		}
		Unit::hasSomeActionBeenStared = false;
		destination = nullptr;
	}

	//right_mouse::Back
	if (Mouse::isButtonPressed(Mouse::Button::Right))
	{
		pathAlgorithm->Onode->unitOn->an_sprite.sprite_y = 0;
		pathAlgorithm->Onode->unitOn->an_sprite.swap_interval = SWAP_INTERVAL; // sec
		turnState->SetActionState(new ChooseTile(gsState, turnState));
	}
}

void TileSelected::draw(state& gsState)
{
	for (auto& tile : pathAlgorithm->path)
	{
		gsState.window.draw(tile->path_sprite);
	}
	for (auto& tile : pathAlgorithm->attackBorderPath)
	{
		gsState.window.draw(tile->path_sprite);
	}
	for (auto tile : pathAlgorithm->attackList)
	{
		gsState.window.draw(tile->path_sprite);
	}
	for (auto tile : pathAlgorithm->nearEnemies)
	{
		gsState.window.draw(tile->path_sprite);
	}
}


