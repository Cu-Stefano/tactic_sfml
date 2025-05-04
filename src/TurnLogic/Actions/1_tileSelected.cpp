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

TileSelected::TileSelected(state& gState, TurnState* turnState, Tile* tile)
	: ActionState(gState, turnState), destination(nullptr)
{
	pathAlgorithm = new PathAlgorithm(tile, gState);
}

void TileSelected::on_enter() {
	Unit::hasSomeActionBeenStared = false;
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

bool TileSelected::move_logic(Tile* hovered_tile, vector<Tile*> route)
{
	Vector2f mousePos = gState.window.mapPixelToCoords(Mouse::getPosition(gState.window));
	if (gState.isMouseOutOfRange(mousePos)) return true;

	if (Mouse::isButtonPressed(Mouse::Button::Left) && !Unit::IsAnyUnitMoving)
	{
		if (!wasButtonPressed)//entra al primo click e poi di nuovo soltanto quando si rilascia left mouse
		{
			wasButtonPressed = true;
			if (hovered_tile == pathAlgorithm->Onode)
			{
				c++;
				if (c < 2) return true;
			}
			else if (!hovered_tile)
					return true;

			if (std::find(pathAlgorithm->Onode->neighbours.begin(), pathAlgorithm->Onode->neighbours.end(), hovered_tile) != pathAlgorithm->Onode->neighbours.end() 
				&& (hovered_tile->unitOn && hovered_tile->unitOn->type == 1))
			{
				std::vector<Tile*> near_enemies{};
				for (auto& neighbour : pathAlgorithm->Onode->neighbours)
				{
					if (neighbour->unitOn && neighbour->unitOn->type == 1 - pathAlgorithm->Onode->unitOn->type)
						near_enemies.push_back(neighbour);
				}
				turnState->SetActionState(new ChooseAttack(gState, turnState, near_enemies, pathAlgorithm->Onode));
				return true;
			}

			currentPosition = gState.getCoordFromTile(hovered_tile);
			//now hovered_tile is the new position of Onode
			destination = hovered_tile;
			pathAlgorithm->Onode->move_unit(hovered_tile, route);
			if (hovered_tile == pathAlgorithm->Onode)
				return false;
		}
	}
	else
	{
		wasButtonPressed = false; // Resetto lo stato quando il pulsante viene rilasciato
	}
	return true;
}

void TileSelected::update()
{
	pathAlgorithm->update();

	//mouse actions:
	Vector2f mousePos = gState.window.mapPixelToCoords(Mouse::getPosition(gState.window));
	auto hovered_tile = gState.get_tile_from_mouse_position(mousePos);
	if (!hovered_tile) return;

	if (!Unit::IsAnyUnitMoving)
	{
		//hover::Trail
		if ((std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), hovered_tile) != pathAlgorithm->path.end() 
			|| hovered_tile == pathAlgorithm->Onode) && destination == nullptr
			|| (std::find(pathAlgorithm->nearEnemies.begin(), pathAlgorithm->nearEnemies.end(), hovered_tile) != pathAlgorithm->nearEnemies.end()))
		{
			std::vector<Tile*> route{};
			if (!hovered_tile->unitOn)
			{
				auto currNode = hovered_tile;
				while (currNode != pathAlgorithm->Onode)
				{
					route.push_back(currNode);
					currNode->shape.setFillColor(ROUTE_COLOR);
					currNode = currNode->Parent;
				}
			}

			if (!move_logic(hovered_tile, route))// è falso se finisco il turno senza spostarmi
			{
				if (gState.check_all_units_moved(0)) 
					gState.MapLogic.set_state(new EnemyTurn(gState));
				else
					turnState->SetActionState(new ChooseTile(gState, turnState));
				return;
			}

			if (Unit::IsAnyUnitMoving)
			{
				for (auto tile : route)
				{
					tile->shape.setFillColor(sf::Color::Transparent);
				}
			}
		}

		if (Unit::hasSomeActionBeenStared)
		{
			//controllo i nighbours per vedere se ci sono nemici.
			std::vector<Tile*> near_enemies{};
			for (auto& neighbour : destination->neighbours)
			{
				if (neighbour->unitOn && neighbour->unitOn->type == 1 - destination->unitOn->type)
				{
					near_enemies.push_back(neighbour);
				}
			}

			if (!near_enemies.empty())
				turnState->SetActionState(new ChooseAttack(gState, turnState, near_enemies, destination));
			else
			{
				destination->unitOn->canMove = false;
				destination->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);

				if (gState.check_all_units_moved(0)) 
					gState.MapLogic.set_state(new EnemyTurn(gState));
				else
					turnState->SetActionState(new ChooseTile(gState, turnState));
			}
			Unit::hasSomeActionBeenStared = false;
		}
	}

	//right_mouse::Back
	if (Mouse::isButtonPressed(Mouse::Button::Right) && !Unit::IsAnyUnitMoving)
	{
		if (pathAlgorithm)
		{
			pathAlgorithm->Onode->unitOn->an_sprite.sprite_y = 0;
			pathAlgorithm->Onode->unitOn->an_sprite.swap_interval = SWAP_INTERVAL; // sec
			turnState->SetActionState(new ChooseTile(gState, turnState));
		}
	}
}

void TileSelected::draw(sf::RenderWindow& window)
{
	if (!Unit::IsAnyUnitMoving && !Unit::hasSomeActionBeenStared)
	{
		for (auto& tile : pathAlgorithm->path)
			gState.window.draw(tile->path_sprite);
		
		for (auto& tile : pathAlgorithm->attackBorderPath)
			gState.window.draw(tile->path_sprite);
		
		for (auto tile : pathAlgorithm->attackList)
			gState.window.draw(tile->path_sprite);
		
		for (auto tile : pathAlgorithm->nearEnemies)
			gState.window.draw(tile->path_sprite);
		
	}
}


