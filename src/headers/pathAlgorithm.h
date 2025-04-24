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
    PathAlgorithm(state& gState);

    void set_origin_tile(Tile* button);
    void execute(bool near = false);

    void reset_all();
    int calculate_distance(Tile* tileToReach) const;

    std::vector<std::vector<Tile*>> initiliazemap();

    Tile* Onode;
    vector<Tile*> path;
    vector<Tile*> attackBorderPath;//i bordi d'attacco del path
    vector<Tile*> attackList;//tutti i nemici dentro al path, ma fuori da nearEnemies
    vector<Tile*> nearEnemies;//nemici nel range di attacco da fermo

private:
    state& gState;
    Unit* unit;
    vector<vector<Tile*>> map;
    std::priority_queue<pair<int, Tile*>, vector<pair<int, Tile*>>, greater<>> priorityQueue;
};

