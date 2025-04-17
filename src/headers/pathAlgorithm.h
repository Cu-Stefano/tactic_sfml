#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "state.h"
#include "unit.h"
using namespace std;

class PathAlgorithm {
public:
    PathAlgorithm(Tile* Onode, state& gs_state);
    PathAlgorithm(state& gs_state);

    void SetOriginTile(Tile* button);
    void Execute(bool near = false);

    void ResetAll();
    int CalculateDistance(Tile* TileToReach) const;

	vector<vector<Tile*>> InitiliazeMap();

    Tile* Onode;
    vector<Tile*> path;
    vector<Tile*> attackBorderPath;//i bordi d'attacco del path
    vector<Tile*> attackList;//tutti i nemici dentro al path, ma fuori da nearEnemies
    vector<Tile*> nearEnemies;//nemici nel range di attacco da fermo

private:
    state& gs_state;
    Unit* unit;
    vector<vector<Tile*>> map;
    priority_queue<pair<int, Tile*>, vector<pair<int, Tile*>>, greater<>> priorityQueue;
  
    //void HandleTileProcessing(Tile* currentTile, int totalRange, int movement, int range);
    //void UpdatePathAndAttackLists(Tile* currentTile, int movement);
};

