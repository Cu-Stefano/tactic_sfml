#include "../../headers/2_chooseAttack.h"

ChooseAttack::ChooseAttack(const state& state, const std::vector<Tile*>& tiles, Tile* tile): ActionState(gs_state, turnState)
{

}
void ChooseAttack::on_enter() {
}
void ChooseAttack::on_exit() {
	// Clean up logic
}

void ChooseAttack::update() {
	
}

void ChooseAttack::draw(state& g_state)
{
}

