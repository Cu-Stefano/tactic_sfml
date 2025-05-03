#pragma once
#include "turnState.hpp"
#include "MapLogic.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Clock.hpp"

class AllayTurn : public TurnState{
public:
    MapLogic* map_logic;
    sf::Text* allay_turn_text;
    sf::Clock textClock;
    explicit AllayTurn(MapLogic* map_logic);

    void on_enter() override;
    void on_exit() override;
    void SetActionState(ActionState* action) override;
    void update() override;
    void draw(state& gState) override;
};
