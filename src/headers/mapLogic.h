#pragma once  
#include "SFML/Graphics/RenderWindow.hpp"

class state;  
class TurnState;

class MapLogic  
{  
public:
	MapLogic(state& gs);
	state& gState;  
	TurnState* current_turnState;  

	void set_state(TurnState* newTurnState);  

	void draw(sf::RenderWindow& window);  
	void update();  
};