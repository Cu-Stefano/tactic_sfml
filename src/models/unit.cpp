#include "../headers/unit.h"
#include "../headers/weapon.h"

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
	can_move = true;

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

    sf::Texture texture;
    std::string path1;
    std::string path2;

    if (type == 0) { // Alleati
        path1 = "resources/Units/0/";
        switch (unit_class) {
        case swordsman:
            path2 = "SwordFighter/SwordFighter_LongHair_Blue1.png";
            break;
        case warrior:
            path2 = "AxeFighter/AxeFighter_LongHair_Blue1.png";
            break;
        case soldier:
            path2 = "SpearFighter/SpearFighter_LongHair_Blue1.png";
            break;
        }
    }
    else { // Nemici
        path1 = "resources/Units/1/";
        switch (unit_class) {
        case swordsman:
            path2 = "SwordFighter/SwordFighter_LongHair_Red1.png";
            break;
        case warrior:
            path2 = "AxeFighter/AxeFighter_ShortHair_Red1.png";
            break;
        case soldier:
            path2 = "SpearFighter/SpearFighter_LongHair_Red1.png";
            break;
        }
    }
    texture.loadFromFile(path1 + path2);
    set_sprite(texture);
}

int Unit::get_attack() const
{
    if (!equiped_weapon.has_value())
    {
        return strength;
    }
    return strength + equiped_weapon.value().damage;
}

int Unit::get_dodge() const
{
	return speed + luck * 2;
}

int Unit::get_hit() const
{
    if (!equiped_weapon.has_value())
    {
        return skill;
    }
    return equiped_weapon.value().hit + skill * 2 + luck;
}

int Unit::get_crit() const
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

std::vector<Unit*> allay_list = {
    new Unit("Ike", 0, ClassType::swordsman, 20, 5, 5, 5, 5, 5, 5),
    new Unit("Mia", 0, ClassType::swordsman, 18, 5, 6, 4, 7, 6, 4),
    new Unit("Oscar", 0, ClassType::warrior, 22, 5, 7, 6, 5, 5, 3),
    new Unit("Boyd", 0, ClassType::warrior, 25, 5, 8, 5, 4, 4, 2),
    new Unit("Rhys", 0, ClassType::soldier, 15, 5, 3, 2, 3, 5, 6),
    new Unit("Soren", 0, ClassType::soldier, 16, 5, 4, 3, 4, 6, 5)
};

std::vector<Unit*> enemy_list = {
    new Unit("Boss", 1, ClassType::warrior, 25, 5, 9, 5, 5, 3, 3),
    new Unit("Sold1", 1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sold2", 1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sold3", 1, ClassType::soldier, 16, 5, 4, 1, 3, 3, 5),
    new Unit("Sword1", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Sword2", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Sword3", 1, ClassType::swordsman, 16, 5, 5, 2, 5, 3, 4),
    new Unit("Warr1", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3),
    new Unit("Warr2", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3),
    new Unit("Warr3", 1, ClassType::warrior, 18, 5, 6, 3, 2, 3, 3)
};
