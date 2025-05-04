#include "../headers/turnState.hpp"
#include "../headers/enemyTurn.h"  

#include "../headers/3_attack.h"
#include "../headers/allayTurn.h"
#include "../headers/mapBuilder.h"
#include "../headers/MapLogic.h"  
#include "../headers/tile.h"
#include "../headers/unit.h"

class Turnstate;

EnemyTurn::EnemyTurn(MapLogic* map_logic) : TurnState(map_logic->gState), pathAlgorithm(nullptr)
{
	this->map_logic = map_logic;
}

void EnemyTurn::initialize_path_algorithm(Tile* unit)
{
	pathAlgorithm = new PathAlgorithm(unit, gState);
	pathAlgorithm->execute();
}

void EnemyTurn::end_enemy_turn(Tile* tile)
{
    tile->unitOn->has_moved();
	tile->unitOn->an_sprite.sprite->setColor(UNIT_MOVED);
	tile->unitOn->canMove = false;
}

void EnemyTurn::attack_allay(Tile* tile)
{

}

void EnemyTurn::on_enter() {
	gState.turn_number->setString("Turn: " + std::to_string(gState.turn));
	Unit::hasSomeActionBeenStared = false; // da mettere a true dopo che un nuita di è mossa 
	iter = enemy_tile_list.begin();
}  

void EnemyTurn::on_exit() {
	for (auto unit : enemy_list)
	{
		unit->canMove = true;
		unit->an_sprite.sprite->setColor(sf::Color::White);
	}
}

Tile* EnemyTurn::get_next_enemy()
{
	if (iter == enemy_tile_list.end())
		iter = enemy_tile_list.begin() + 1;
    else if (enemy_tile_list.empty()) {
        return nullptr; // Nessun nemico rimasto
    }

    Tile* next_enemy = *iter;
    ++iter;
    return next_enemy;

}

Tile* EnemyTurn::find_tile_to_land(Tile* attackedUnit)
{
	int cost = 100;
	Tile* finalTile = nullptr;

	// Ricorsione sui vicini
	for (Tile* neighbor : attackedUnit->neighbours)
	{
		if (neighbor->walkable && std::find(pathAlgorithm->path.begin(), pathAlgorithm->path.end(), neighbor) != pathAlgorithm->path.end())
		{
			int currentCost = pathAlgorithm->calculate_distance(neighbor);
			if (currentCost < cost)
			{
				cost = currentCost;
				finalTile = neighbor;
			}
		}
	}

	return finalTile;
}

void EnemyTurn::move_towards_allay()
{
	int range = current_enemy->unitOn->name == "Boss" ? 50: 15;

	pathAlgorithm = new PathAlgorithm(current_enemy, gState);
	pathAlgorithm->execute(range);

	if (pathAlgorithm->attackList.empty())
	{
		end_enemy_turn(current_enemy);
		current_phase = turn_fase::END;
		return;
	}

	auto allayToPoint = pathAlgorithm->attackList[0];
	auto tile = find_tile_to_land(allayToPoint);
	if (!tile)
	{
		end_enemy_turn(current_enemy);
		current_phase = turn_fase::END;
		return;
	}
	// set the route
	auto currNode = tile;
	std::deque<Tile*> routeAux{};
	while (currNode != pathAlgorithm->Onode)
	{
		routeAux.push_back(currNode);
		currNode = currNode->Parent;
	}

	// tolgo i tile che non puo raggiungere
	currNode = routeAux[0];
	int size = routeAux.size();
    for (int i = 0; i < (size - current_enemy->unitOn->movement); i++)
    {
		routeAux.pop_front();
		currNode = routeAux[0];
    }
	tileToLand = currNode;
	route = std::vector(routeAux.begin(), routeAux.end());
	current_phase = turn_fase::PROCESSING_TURN;
}

void EnemyTurn::update() {

	switch (current_phase) {

	case turn_fase::TURN_NAME:

		if (clock.getElapsedTime().asSeconds() <= 3.0f)
			break;
		clock = sf::Clock();
		current_phase = turn_fase::IDLE;
		break;

	case turn_fase::IDLE:

		Unit::hasSomeActionBeenStared = false;
		current_enemy = get_next_enemy();
		if (gState.check_all_units_moved(1))
		{
			gState.MapLogic.set_state(new AllayTurn(&gState.MapLogic));
			return;
		}

		if (current_enemy && current_enemy->unitOn && current_enemy->unitOn->canMove) {

			current_phase = turn_fase::SHOW_PATH;
			initialize_path_algorithm(current_enemy);

			// c'e' un nemico vicino, attacca quello
			if (!pathAlgorithm->nearEnemies.empty())
			{
				allayToAttack = pathAlgorithm->nearEnemies[0];
				current_phase = turn_fase::SHOW_ATTACK_GUI;
				tileToLand = current_enemy;
				break;
			}

			if (pathAlgorithm->attackList.empty())
			{
				if (gState.turn >= 3)
				{
					move_towards_allay();
					break;
				}
				end_enemy_turn(current_enemy);
				current_phase = turn_fase::END;
				return;
			}

			allayToAttack = pathAlgorithm->attackList[0];
			tileToLand = find_tile_to_land(allayToAttack);

			auto currNode = tileToLand;
			while (currNode != pathAlgorithm->Onode)
			{
				route.push_back(currNode);
				currNode->shape.setFillColor(ROUTE_COLOR);
				currNode = currNode->Parent;
			}

			if (tileToLand == nullptr)
			{
				end_enemy_turn(current_enemy);
				current_phase = turn_fase::END;
				return;
			}
			current_phase = turn_fase::SHOW_PATH;
		}

		break;

	case turn_fase::SHOW_PATH:
	{
		pathAlgorithm->update();

		auto routeColor = ENEMY_ROUTE_COLOR;

		if (clock.getElapsedTime().asSeconds() >= 2.0f)
		{
			routeColor = sf::Color::Transparent;
			current_phase = turn_fase::PROCESSING_TURN;
			clock = sf::Clock();
		}

		for (auto tile : route)
		{
			tile->shape.setFillColor(routeColor);
		}

		break;
	}
    case turn_fase::PROCESSING_TURN:

		current_enemy->unitOn->an_sprite.swap_interval = SWAP_INTERVAL_RUN;
		current_enemy->unitOn->an_sprite.sprite_y = 1;
		pathAlgorithm->Onode->move_unit(tileToLand, route);

		current_phase = turn_fase::SHOW_ATTACK_GUI;
        break;

    case turn_fase::SHOW_ATTACK_GUI:

		if (Unit::IsAnyUnitMoving && Unit::hasSomeActionBeenStared)
			break;

		if (!allayToAttack)// nemico che si è avvicinato 
		{
			end_enemy_turn(tileToLand);
			*(iter - 1) = tileToLand;
			Unit::hasSomeActionBeenStared = false;
			previewSelected = true;
			current_phase = turn_fase::END;
			clock = sf::Clock();
			break;
		}

		//he arrived
		*(iter - 1) = tileToLand;
		current_enemy = tileToLand;
		Unit::hasSomeActionBeenStared = false;
		
		previewSelected = true;
		gState.attackGui.initializer(current_enemy, allayToAttack);
		gState.attackGui.update();

		current_enemy->unitOn->an_sprite.sprite_y = 0;
		current_enemy->unitOn->an_sprite.swap_interval = SWAP_INTERVAL; // sec

		if (clock.getElapsedTime().asSeconds() <= 3.0f)
			break;

		current_phase = turn_fase::ATTACK;
		gState.attackGui.attack_initiated = true;
		attackState = new Attack(gState, this, current_enemy, gState.attackGui.unitB, gState.attackGui.unitAStats, gState.attackGui.unitBStats);
		gState.MapLogic.current_turnState->SetActionState(attackState);
		break;

	case turn_fase::ATTACK:

		CurrentActionState->update();
		if (attackState->attackFinished)
		{
			clock = sf::Clock();
			if (!current_enemy->unitOn || current_enemy->unitOn->canMove)// quello prima e' morto
				--iter;
			current_phase = turn_fase::END;
		}
		break;
	case turn_fase::END:

		if (clock.getElapsedTime().asSeconds() <= 1.0f)
			break;

		previewSelected = false;
		gState.attackGui.attack_initiated = false;
		allayToAttack = nullptr;
		tileToLand = nullptr;
		current_phase = turn_fase::IDLE;
		clock = sf::Clock();
		route.clear();
		pathAlgorithm->reset_all();
		break;
    }
}  

void EnemyTurn::draw(state& gState)
{
	gState.window.draw(*gState.turn_number);

   switch (current_phase) {

   case turn_fase::TURN_NAME:{
   		sf::Text enemy_turn_text = sf::Text(gState.font, "ENEMY TURN", 40);
   		enemy_turn_text.setPosition({ static_cast<float>(gState.menubar_attack_window_x / 3), static_cast<float>(gState.menubar_attack_y / 3) });
		enemy_turn_text.setFillColor(sf::Color::Red);
   		gState.window.draw(enemy_turn_text);
   }break;
   case turn_fase::IDLE:

	   break;
   case turn_fase::SHOW_PATH:

   	for (auto& tile : pathAlgorithm->path)
   		gState.window.draw(tile->path_sprite);

   	for (auto& tile : pathAlgorithm->attackBorderPath)
   		gState.window.draw(tile->path_sprite);

   	for (auto tile : pathAlgorithm->attackList)
   		gState.window.draw(tile->path_sprite);

   	for (auto tile : pathAlgorithm->nearEnemies)
   		gState.window.draw(tile->path_sprite);

	   break;

   case turn_fase::PROCESSING_TURN:
	   break;

   case turn_fase::SHOW_ATTACK_GUI:
	   if (previewSelected)
	   {
		   gState.attackGui.draw_units();
		   gState.attackGui.draw_stats();
		   break;
	   }
	   break;

   case turn_fase::ATTACK:
	   CurrentActionState->draw(gState);
	   break;
   case turn_fase::END:
	   break;
   }
}
