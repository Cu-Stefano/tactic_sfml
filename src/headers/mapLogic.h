#pragma once  
class state;  
class TurnState;

class MapLogic  
{  
public:
	MapLogic(state& gs);
	state& gState;  
	TurnState* current_turnState;  

	void set_state(TurnState* newTurnState);  

	void draw(state& gState) const;  
	void update() const;  
};