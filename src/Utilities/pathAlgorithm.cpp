#include "../headers/pathAlgorithm.h"

#include <random>
#include <stdbool.h>

PathAlgorithm::PathAlgorithm(Tile* Onode, state& gs_state): gs_state(gs_state)
{
	map = InitiliazeMap();
	priorityQueue = {}; // emplace, top, pop
	path = {};
	attackBorderPath = {};
	attackList = {};
	nearEnemies = {};

	this->Onode = Onode;
	unit = Onode->UnitOn;
	Onode->G = 0; 
	Onode->Parent = nullptr; 
    priorityQueue.emplace(Onode->G = 0, Onode);
}
PathAlgorithm::PathAlgorithm(state& gs_state) : gs_state(gs_state)
{
	map = InitiliazeMap();
	priorityQueue = {};
	path = {};
	attackBorderPath = {};
	attackList = {};
	nearEnemies = {};
	this->Onode = nullptr;
	unit = nullptr;
}
void PathAlgorithm::SetOriginTile(Tile* button)
{
	this->Onode = Onode;
	unit = Onode->UnitOn;
	Onode->G = 0;
	Onode->Parent = nullptr;
	priorityQueue.emplace(Onode->G = 0, Onode);
}

void PathAlgorithm::Execute(bool near)
{
    auto enemyType = unit->type == 0 ? 1 : 0; //the type of units the Onode wants to attack
    int movement = unit->movement;
    int range = unit->equiped_weapon ? unit->equiped_weapon->range : 0;
    int totalRange = near ? range : movement + range;

    while (!priorityQueue.empty())
    {
        auto curr = priorityQueue.top().second;// Implementa GetNextNode per ottenere il prossimo nodo
        if (!curr) continue;
        priorityQueue.pop();

        if ((curr == Onode || curr->passable) && curr->G < totalRange && std::find(path.begin(), path.end(), curr) == path.end())
        {
            for (auto& currNeighbour : curr->Neighbours)
            {
                if (currNeighbour->G == 0) 
                {
                    if (currNeighbour->UnitOn && currNeighbour->UnitOn->type == enemyType && curr->G < range && std::find(nearEnemies.begin(), nearEnemies.end(), currNeighbour) == nearEnemies.end())
                    {
                        nearEnemies.push_back(currNeighbour);
                        continue;
                    }

                    if (currNeighbour->UnitOn)
                    {
                        if (currNeighbour->UnitOn->type == enemyType)
                            attackList.push_back(currNeighbour);
                        continue;
                    }

                    currNeighbour->G = curr->G + 1;
                    currNeighbour->Parent = curr;
                    priorityQueue.emplace(currNeighbour->G, currNeighbour);
                }
            }
        }

        if (curr->G > movement)
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

void PathAlgorithm::ResetAll()
{
	//ricolora i currNeighbour delle 3 liste vector
	for (auto& currNeighbour : path)
	{
		currNeighbour->shape.setFillColor(sf::Color::Transparent);
	}
	for (auto& currNeighbour : attackBorderPath)
	{
		currNeighbour->shape.setFillColor(sf::Color::Transparent);
	}
	for (auto& currNeighbour : attackList)
	{
		currNeighbour->shape.setFillColor(sf::Color::Transparent);
	}
}

int PathAlgorithm::CalculateDistance(Tile* currNeighbourToReach) const
{
	auto c = 0;
	auto currNode = currNeighbourToReach;
	while (currNode != this->Onode)
	{
		currNode = currNode->Parent;
		c++;
	}
	return c;
}

vector<vector<Tile*>> PathAlgorithm::InitiliazeMap()  
{  
   auto& baseMap = gs_state.Map;
   vector<vector<Tile*>> result;  

   
   for (int i = 0; i < baseMap.size(); i++)  
   {  
       vector<Tile*> row;  
       for (int j = 0; j < baseMap[0].size(); j++)  
       {  
           Tile* tile = baseMap[i][j];  
           tile->G = 0;
           tile->passable = tile->UnitOn != nullptr ? true: tile->Walkable;
           row.push_back(tile);
       }  
       result.push_back(row);  
   }  

   //neighbours
   for (int k = 0; k < baseMap.size(); k++)  
   {  
       for (int l = 0; l < baseMap[0].size(); l++)  
       {  
           auto& node = result[k][l];  
           if (k > 0 && result[k - 1][l]->passable)
               node->Neighbours.push_back(result[k - 1][l]);

           if (l > 0 && result[k][l - 1]->passable)
               node->Neighbours.push_back(result[k][l - 1]);

           if (k < baseMap.size() - 1 && result[k + 1][l]->passable)
               node->Neighbours.push_back(result[k + 1][l]);

           if (l < baseMap[k].size() - 1 && result[k][l + 1]->passable)
               node->Neighbours.push_back(result[k][l + 1]);
       }  
   }  

   return result;  
}


