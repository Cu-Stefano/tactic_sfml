#pragma once
#include <string>
#include <optional>
#include "animatedSprite.h"
#include "weapon.h"

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

    int Get_Dodge() const;
    int Get_Hit() const;
    int Get_Attack() const;
    int Get_Crit() const;

    void draw(sf::RenderWindow& window) const;
	void update();
};
//in modo che non vengano ridefinite, senza i puntatori cambiano di valore
extern std::vector<Unit*> allay_list;
extern std::vector<Unit*> enemy_list;

