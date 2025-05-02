#include "../headers/turnState.hpp"
#include "../headers/enemyTurn.h"  

#include "../headers/3_attack.h"
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
	Unit::hasSomeActionBeenStared = false; // da mettere a true dopo che un nuita di è mossa 
	iter = enemy_tile_list.begin();
}  

void EnemyTurn::on_exit() {
     
}

Tile* EnemyTurn::get_next_enemy()
{
    
    if (iter == enemy_tile_list.end() || enemy_tile_list.empty()) {
        return nullptr; // Nessun nemico rimasto
    }

    Tile* next_enemy = *iter;
    ++iter;
    return next_enemy;

}

Tile* EnemyTurn::find_tile_to_land(Tile* attackedUnit)
{
	int cost = 10;
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

void EnemyTurn::update() {

	switch (current_phase) {

	case turn_fase::TURN_NAME:
		if (showPathClock.getElapsedTime().asSeconds() <= 3.0f)
			break;
		showPathClock = sf::Clock();
		current_phase = turn_fase::IDLE;
		break;
	case turn_fase::IDLE:

		current_enemy = get_next_enemy();
		if (current_enemy && current_enemy->unitOn->canMove) {

			current_phase = turn_fase::SHOW_PATH;
			initialize_path_algorithm(current_enemy);

			if (pathAlgorithm->nearEnemies[0] != nullptr)
			{
				allayToAttack = pathAlgorithm->nearEnemies[0];
				current_phase = turn_fase::SHOW_ATTACK_GUI;
				tileToLand = current_enemy;
				break;
			}

			allayToAttack = pathAlgorithm->attackList[0];
			if (allayToAttack == nullptr)
			{
				end_enemy_turn(current_enemy);
				current_phase = turn_fase::IDLE;
				return;
			}

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
				current_phase = turn_fase::IDLE;
				return;
			}
			current_phase = turn_fase::SHOW_PATH;
		}
		break;

	case turn_fase::SHOW_PATH:
	{
		for (auto& tile : pathAlgorithm->path)
		{
			tile->path_sprite.setColor(ENEMY_PATH_COLOR);
			tile->shape.setFillColor(sf::Color::Transparent);
		}
		for (auto& tile : pathAlgorithm->attackBorderPath)
			tile->path_sprite.setColor(ENEMY_ATTACK_COLOR);

		for (auto tile : pathAlgorithm->attackList)
			tile->path_sprite.setColor(ENEMY_ATTACK_COLOR);

		for (auto tile : pathAlgorithm->nearEnemies)
			tile->path_sprite.setColor(ENEMY_ATTACK_COLOR);

		auto routeColor = ENEMY_ROUTE_COLOR;

		if (showPathClock.getElapsedTime().asSeconds() >= 2.0f)
		{
			routeColor = sf::Color::Transparent;
			current_phase = turn_fase::PROCESSING_TURN;
			showPathClock = sf::Clock();
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

		//he arrived
		previewSelected = true;
		current_enemy = tileToLand;

		gState.attackGui.unitA = current_enemy;
		gState.attackGui.unitB = allayToAttack;
		gState.attackGui.unitAStats = {};
		gState.attackGui.unitBStats = {};
		gState.attackGui.update();

		current_enemy->unitOn->an_sprite.sprite_y = 0;
		current_enemy->unitOn->an_sprite.swap_interval = SWAP_INTERVAL; // sec

		/*if (showAttackGuiClock.getElapsedTime().asSeconds() <= 10.0f)
			break;*/

		//CurrentActionState = new Attack(gState, this, current_enemy, gState.attackGui.unitB, gState.attackGui.unitAStats, gState.attackGui.unitBStats);
		break;

	case turn_fase::END:
		gState.attackGui.attack_initiated = false;
		break;
    }
}  

void EnemyTurn::draw(state& gState)
{
   static bool firstTime = true; // Flag to check if it's the first time entering

   if (firstTime) {
       firstTime = false; // Set the flag to false after the first entry
       return; // Exit immediately without doing anything
   }

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

   case turn_fase::END:
	   break;
   }
}
