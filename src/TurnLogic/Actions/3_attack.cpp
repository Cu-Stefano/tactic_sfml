#include "../../headers/3_attack.h"


Attack::Attack(state& state, TurnState* turnState, Tile* unitA, Tile* unitB, std::vector<int> aStats, std::vector<int> bStats):
	ActionState(state, turnState), unitA(unitA), unitB(unitB), aStats(aStats), bStats(bStats)
{
}

void Attack::on_enter()
{
	
}

void Attack::on_exit()
{
	
}

void Attack::update()
{

}
void Attack::draw(state& gState)
{

}





