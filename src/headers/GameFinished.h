#pragma once
#include "turnState.hpp"

class GameFinished : public TurnState {
public:
	GameFinished(state& gs, sf::String state);
    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text* win_state;
};
