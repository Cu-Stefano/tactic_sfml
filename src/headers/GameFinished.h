#pragma once
#include "turnState.hpp"
#include "MapLogic.h"


class GameFinished : public TurnState {
public:
	GameFinished(MapLogic* map_logic, sf::String state);

    void update() override;
    void draw(state& gState) override;

private:
    sf::Text* state;
};
