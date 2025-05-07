#pragma once
#include "turnState.hpp"
#include "button.h"
#include "SFML/System/Clock.hpp"

class AllayTurn : public TurnState{
public:
    sf::Text* allay_turn_text;
    sf::Clock textClock;
    sf::Texture ui;
    Button* speedUpButton;
    explicit AllayTurn(state& gs);

    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};
