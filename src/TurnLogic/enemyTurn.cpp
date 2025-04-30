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

void EnemyTurn::update() {

    switch (current_phase) {

    case turn_fase::IDLE:
        current_enemy = get_next_enemy();
        if (current_enemy) {
            current_phase = turn_fase::SHOW_PATH;
			initialize_path_algorithm(current_enemy);
        }
        break;

	case turn_fase::SHOW_PATH:

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

		if (showPathClock.getElapsedTime().asSeconds() <= 3.0f)
			current_phase = turn_fase::PROCESSING_TURN;

		break;

    case turn_fase::PROCESSING_TURN:
		if (current_enemy->unitOn->canMove) {
			auto allayToAttack = pathAlgorithm->attackList[0];
			if (allayToAttack == nullptr)
			{
				end_enemy_turn(current_enemy);
				current_phase = turn_fase::IDLE;
				return;
			}
			if (std::find(pathAlgorithm->nearEnemies.begin(), pathAlgorithm->nearEnemies.end(), allayToAttack) != pathAlgorithm->nearEnemies.end())
			{
				gState.attackGui.unitA = current_enemy;
				gState.attackGui.unitB = allayToAttack;
				gState.attackGui.unitAStats = {};
				gState.attackGui.unitBStats = {};
				gState.attackGui.update();

				current_phase = turn_fase::SHOW_ATTACK_GUI;
				return;
			}
		}
        current_phase = turn_fase::END;
        break;

    case turn_fase::SHOW_ATTACK_GUI:

		if (showAttackGuiClock.getElapsedTime().asSeconds() <= 3.0f)
			break;
		
		//CurrentActionState = new Attack(gState, this, current_enemy, gState.attackGui.unitB, gState.attackGui.unitAStats, gState.attackGui.unitBStats);
		break;

	case turn_fase::END:
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

   case turn_fase::IDLE:
	   break;

   case turn_fase::SHOW_PATH:
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
	   break;

   case turn_fase::PROCESSING_TURN:

	   break;

   case turn_fase::SHOW_ATTACK_GUI:

	   break;

   case turn_fase::END:
	   break;
   }
}
