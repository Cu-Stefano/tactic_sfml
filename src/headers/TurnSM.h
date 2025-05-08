#pragma once  
#include "SFML/Graphics/RenderWindow.hpp"

class state;  
class TurnState;

class TurnSM  
{  
public:
	TurnSM(state& gs);
	state& gState;  
	TurnState* current_turnState;  

	void set_state(TurnState* newTurnState);  

	void draw(sf::RenderWindow& window) const;  
	void update() const;  
};