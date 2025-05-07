#include "../headers/pathAlgorithm.h"

#include <iostream>

#include "../headers/state.hpp"
#include "../headers/tile.h"
#include "../headers/unit.h"
#include "../headers/weapon.h"
#include <random>

PathAlgorithm::PathAlgorithm(Tile* Onode, state& gState): gState(gState)
{
	map = initiliazemap();
	priorityQueue = {}; // emplace, top, pop
	path = {};
	attackBorderPath = {};
	attackList = {};
	nearEnemies = {};

	this->Onode = Onode;
	unit = Onode->unitOn;
	Onode->G = 0; 
	Onode->Parent = nullptr; 
    priorityQueue.emplace(Onode->G = 0, Onode);
}
PathAlgorithm::PathAlgorithm(state& gState) : gState(gState)
{
	map = initiliazemap();
	priorityQueue = {};
	path = {};
	attackBorderPath = {};
	attackList = {};
	nearEnemies = {};
	this->Onode = nullptr;
	unit = nullptr;
}
void PathAlgorithm::set_origin_tile(Tile* button)
{
	this->Onode = Onode;
	unit = Onode->unitOn;
	Onode->G = 0;
	Onode->Parent = nullptr;
	priorityQueue.emplace(Onode->G = 0, Onode);
}

void PathAlgorithm::execute(int range)
{
    auto enemyType = unit->type == 0 ? 1 : 0; //the type of units the Onode wants to attack
    int movement = unit->movement;
    int totalRange = movement + range;

    while (!priorityQueue.empty())
    {
        auto curr = priorityQueue.top().second;// Implementa GetNextNode per ottenere il prossimo nodo
        if (!curr) continue;
        priorityQueue.pop();

        if ((curr == Onode || curr->passable) && curr->G < totalRange && std::find(path.begin(), path.end(), curr) == path.end())
        {
            for (auto& currNeighbour : curr->neighbours)
            {
                if (currNeighbour->G == 0) 
                {
                    if (currNeighbour->unitOn 
                        && currNeighbour->unitOn->type == enemyType 
                        && curr->G < range 
                        && std::find(nearEnemies.begin(), nearEnemies.end(), currNeighbour) == nearEnemies.end())
                    {
                        nearEnemies.push_back(currNeighbour);
                        continue;
                    }

                    if (currNeighbour->unitOn)
                    {
                        if (currNeighbour->unitOn->type == enemyType)
                            attackList.push_back(currNeighbour);
                    }

                    currNeighbour->G = curr->G + 1;
                    currNeighbour->Parent = curr;
                    priorityQueue.emplace(currNeighbour->G, currNeighbour);
                }
            }
        }

        if (curr->G > totalRange - 1)
        {
            attackBorderPath.push_back(curr);
        }
        else if (curr != Onode)
        {
            path.push_back(curr);
        }
            
    }

    for (auto& butt : nearEnemies)
    {
        if (std::find(attackList.begin(), attackList.end(), butt) == attackList.end())
            attackList.push_back(butt);
    }
}

void PathAlgorithm::reset_all()
{
	//reet dei colori

	for (auto& tile : path)
	{
        tile->path_sprite.setColor(sf::Color::Transparent);
        tile->shape.setFillColor(sf::Color::Transparent);
	}
	
	for (auto& tile : attackBorderPath)
		tile->path_sprite.setColor(sf::Color::Transparent);
	
	for (auto& tile : attackList)
		tile->path_sprite.setColor(sf::Color::Transparent);
	
	for (auto& tile : nearEnemies)
		tile->path_sprite.setColor(sf::Color::Transparent);
	
}

int PathAlgorithm::calculate_distance(Tile* tileToReach) const
{
	auto c = 0;
	auto currNode = tileToReach;
	while (currNode != this->Onode)
	{
		currNode = currNode->Parent;
		c++;
	}
	return c;
}

vector<vector<Tile*>> PathAlgorithm::initiliazemap()  
{
    for (auto tiles : gState.map)
    {
        for (auto tile : tiles)
        {
            //reset dei neighbours
            tile->neighbours.clear();
        }
    }

   auto basemap = gState.map;
   vector<vector<Tile*>> result;

   for (int i = 0; i < basemap.size(); i++)  
   {  
       vector<Tile*> row;  
       for (int j = 0; j < basemap[0].size(); j++)  
       {  
           Tile* tile = basemap[i][j];  
           tile->G = 0;
           tile->passable = tile->unitOn != nullptr ? true: tile->walkable;
           row.push_back(tile);
       }  
       result.push_back(row);  
   }  

   //neighbours
   for (int k = 0; k < basemap.size(); k++)  
   {  
       for (int l = 0; l < basemap[0].size(); l++)  
       {  
           auto& node = result[k][l];  
           if (k > 0 && result[k - 1][l]->passable)
               node->neighbours.push_back(result[k - 1][l]);

           if (l > 0 && result[k][l - 1]->passable)
               node->neighbours.push_back(result[k][l - 1]);

           if (k < basemap.size() - 1 && result[k + 1][l]->passable)
               node->neighbours.push_back(result[k + 1][l]);

           if (l < basemap[k].size() - 1 && result[k][l + 1]->passable)
               node->neighbours.push_back(result[k][l + 1]);
       }  
   }  

   return result;  
}

void PathAlgorithm::update()
{
	auto path_color = unit->type == 0 ? ALLAY_PATH_COLOR : ENEMY_PATH_COLOR;
	auto attack_color = unit->type == 0 ? ALLAY_ATTACK_COLOR : ENEMY_ATTACK_COLOR;

    for (auto& tile : path)
    {
        tile->path_sprite.setColor(path_color);
        tile->shape.setFillColor(sf::Color::Transparent);
    }
    for (auto& tile : attackBorderPath)
        tile->path_sprite.setColor(attack_color);

    for (auto tile :attackList)
        tile->path_sprite.setColor(attack_color);

    for (auto tile : nearEnemies)
        tile->path_sprite.setColor(attack_color);
}

