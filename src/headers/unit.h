#pragma once

#include <string>
#include <optional>
#include "animatedSprite.h"
#include "animState.h"
#include "weapon.h"

class AnimState;

enum ClassType
{
	swordsman = 0,
	warrior = 1,
	soldier = 2,
};

class Unit {
public:
    std::string name;
    bool type; // 0 allay, 1 enemy
    bool can_move;
    ClassType unit_class;
    std::optional<Weapon> equiped_weapon;
    
    AnimatedSprite an_sprite;
    AnimState* anim_state;

    //stats
    int hp;
    int movement;
    int max_hp;
    int strength;
    int defense;
    int speed;
    int skill;
    int luck;

    Unit() = default;
    Unit(std::string n, bool t, ClassType c, int mh,int mv, int str, int def, int spe, int skl, int lck);

    void set_sprite(sf::Texture t);
    void set_sprite_pos(sf::Vector2i coord);
    void set_state(AnimState* a);

    int Get_Dodge() const;
    int Get_Hit() const;
    int Get_Attack() const;
    int Get_Crit() const;

    void draw(sf::RenderWindow& window) const;
	void update();
};

static std::vector<Unit*> allay_list = {
    new Unit("Ike", 0, ClassType::swordsman, 20,5, 5, 5, 5, 5, 5),
    new Unit("Mia", 0, ClassType::swordsman, 18, 5, 6, 4, 7, 6, 4),
    new Unit("Oscar", 0, ClassType::warrior, 22, 5, 7, 6, 5, 5, 3),
    new Unit("Boyd", 0, ClassType::warrior, 25, 5, 8, 5, 4, 4, 2),
    new Unit("Rhys", 0, ClassType::soldier, 15, 5, 3, 2, 3, 5, 6),
    new Unit("Soren", 0, ClassType::soldier, 16,5, 4, 3, 4, 6, 5)
};

static std::vector<Unit*> enemy_list = {
    new Unit("Boss", 1, ClassType::warrior, 25, 5, 9, 5, 5, 3, 3),
    new Unit("Sold1",1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sold2",1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sold3",1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sword1", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Sword2", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Sword3", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Warr1", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3),
    new Unit("Warr2", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3),
    new Unit("Warr3", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3),
};
