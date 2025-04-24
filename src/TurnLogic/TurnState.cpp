#include "../headers/turnState.hpp"
#include "../headers/actionState.hpp"

void TurnState::SetActionState(ActionState* action) {
    if (CurrentActionState) {
        CurrentActionState->on_exit();
    }
    CurrentActionState = action;
    if (CurrentActionState) {
        CurrentActionState->on_enter();
    }
}
