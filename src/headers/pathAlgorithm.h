#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
using std::vector, std::priority_queue, std::pair, std::greater;

class Unit;
class Tile;
class state;

class PathAlgorithm {
public:
    PathAlgorithm(Tile* Onode, state& gState);

    void execute(int range = 1);
    void reset_all() const;
    int calculate_distance(const Tile* tileToReach) const;

    std::vector<std::vector<Tile*>> initiliazemap() const;
    void update() const;

    Tile* Onode;
    vector<Tile*> path;
    vector<Tile*> attackBorderPath; //the border of the path 
    vector<Tile*> attackList;// all the enemies in his range
    vector<Tile*> nearEnemies; // the enemies that are neighbours to oNode
    

private:
    state& gState;
    Unit* unit;
    int enemyType;
    vector<vector<Tile*>> map;
    std::priority_queue<pair<int, Tile*>, vector<pair<int, Tile*>>, greater<>> priorityQueue;
};

