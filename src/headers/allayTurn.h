#pragma once
#include "turnState.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Clock.hpp"

class AllayTurn : public TurnState{
public:
    sf::Text* allay_turn_text;
    sf::Clock textClock;
    explicit AllayTurn(state& gs);

    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};
