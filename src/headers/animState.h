#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "animatedSprite.h"
#include "unit.h"

class Unit;

class AnimState {
public:
    AnimState(Unit* unit);
    virtual void on_enter() = 0;

protected:
    Unit* unit;
};

class IdleState : public AnimState {
public:
	IdleState(Unit* unit) : AnimState(unit) {}
    void on_enter() override;
};

class MoveState : public AnimState {
public:
    MoveState(Unit* unit) : AnimState(unit) {}
    void on_enter() override;
};

class AttackState : public AnimState {
public:
    AttackState(Unit* unit) : AnimState(unit) {}
    void on_enter() override;
};

class DeathState : public AnimState {
public:
    DeathState(Unit* unit) : AnimState(unit) {}
    void on_enter() override;
};
