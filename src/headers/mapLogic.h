#pragma once  
#include "turnState.hpp"  

class state;  

class MapLogic  
{  
public:
	MapLogic(state& gs);
	state& gs_state;  
	TurnState* current_turnState;  

	void SetState(TurnState* newTurnState);  

	void draw(state& g_state) const;  
	void update() const;  
};