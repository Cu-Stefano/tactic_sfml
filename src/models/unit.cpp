#include "../headers/unit.h"

Unit::Unit(std::string n, bool t, ClassType c, int mh, int mv, int str, int def, int spe, int skl, int lck)
{
	name = n;
	type = t;
	unit_class = c;
	max_hp = mh;
	movement = mv;
	hp = mh;
	strength = str;
	defense = def;
	speed = spe;
	skill = skl;
	luck = lck;

	switch (c)
	{
	case ClassType::swordsman:
		equiped_weapon = Weapon(1, 7, 80, 10, WeaponType::sword);
		break;
	case ClassType::warrior:
		equiped_weapon = Weapon(1, 8, 70, 8, WeaponType::axe);
		break;
	case ClassType::soldier:
		equiped_weapon = Weapon(1, 6, 100, 5, WeaponType::lance);
		break;
	}

    set_state(new IdleState(this));
}

void Unit::set_state(AnimState* a)
{
    anim_state = a;
	anim_state->on_enter();
}

int Unit::Get_Attack() const
{
    if (!equiped_weapon.has_value())
    {
        return strength;
    }
    return strength + equiped_weapon.value().damage;
}

int Unit::Get_Dodge() const
{
	return speed + luck * 2;
}

int Unit::Get_Hit() const
{
    if (!equiped_weapon.has_value())
    {
        return skill;
    }
    return equiped_weapon.value().hit + skill * 2 + luck;
}

int Unit::Get_Crit() const
{
    if (!equiped_weapon.has_value())
    {
        return skill;
    }
    return equiped_weapon.value().critical + skill / 2;
}

void Unit::set_sprite(sf::Texture t)
{
	an_sprite = *new AnimatedSprite(t);
}

void Unit::set_sprite_pos(sf::Vector2i coord)
{
    an_sprite.set_pos(coord);
}

void Unit::draw(sf::RenderWindow& window) const
{
	an_sprite.draw(window);
}

void Unit::update()
{
	an_sprite.update();
}
