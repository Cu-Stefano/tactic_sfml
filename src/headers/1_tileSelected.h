#pragma once

#include "actionState.hpp"
#include "button.h"

class Tile;
class PathAlgorithm;

class TileSelected : public ActionState {
	Tile* destination;
	PathAlgorithm* pathAlgorithm;
	Button* unguento;
	Tile* tile;    

public:
	TileSelected(state& gState, TurnState* turnState, Tile* tile);
	void on_enter() override;
	void on_exit() override;
	bool move_logic(Tile* tile, std::vector<Tile*> route);

	void update() override;
	void draw(sf::RenderWindow& window) override;
};
