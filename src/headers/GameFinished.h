#pragma once
#include "turnState.hpp"

class GameFinished : public TurnState {
public:
	GameFinished(state& gs, sf::String state);

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text* win_state;
};
