#include <iostream>
#include "../headers/unit.h"
#include "../headers/weapon.h"
#include "../headers/tile.h"

bool Unit::IsAnyUnitMoving = false;
bool Unit::hasSomeActionBeenStared = false;
using namespace sf;

Unit::Unit(std::string n, bool t, ClassType c, int mh, int mv, int str, int def, int spe, int skl, int lck)
    : name(n), type(t), unit_class(c), max_hp(mh), movement(mv), hp(mh),
    strength(str), defense(def), speed(spe), skill(skl), luck(lck), canMove(true)
{
    equiped_weapon = initialize_weapon(c);
    Texture texture = load_texture(type, unit_class);
    set_sprite(texture);
}

Weapon Unit::initialize_weapon(ClassType c) const {
    switch (c) {
    case ClassType::swordsman:
        return Weapon(1, 7, 80, 10, WeaponType::sword);
    case ClassType::warrior:
        return Weapon(1, 8, 70, 8, WeaponType::axe);
    case ClassType::soldier:
        return Weapon(1, 6, 100, 5, WeaponType::lance);
    }
    throw std::invalid_argument("Invalid ClassType");
}

Texture Unit::load_texture(int type, ClassType unit_class) const {
    std::string path1 = type == 0 ? "resources/Units/0/" : "resources/Units/1/";
    std::string path2;

    switch (unit_class) {
    case ClassType::swordsman:
        path2 = type == 0 ? "SwordFighter/SwordFighter_LongHair_Blue1.png" : "SwordFighter/SwordFighter_LongHair_Red1.png";
        break;
    case ClassType::warrior:
        path2 = type == 0 ? "AxeFighter/AxeFighter_LongHair_Blue1.png" : "AxeFighter/AxeFighter_ShortHair_Red1.png";
        break;
    case ClassType::soldier:
        path2 = type == 0 ? "SpearFighter/SpearFighter_LongHair_Blue1.png" : "SpearFighter/SpearFighter_LongHair_Red1.png";
        break;
    }

    Texture texture;
    if (!texture.loadFromFile(path1 + path2)) {
        throw std::runtime_error("Failed to load texture: " + path1 + path2);
    }
    return texture;
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

void Unit::set_sprite(Texture t)
{
	an_sprite = *new AnimatedSprite(t);
}

void Unit::set_sprite_pos(Vector2i coord)
{
    an_sprite.set_pos(coord);
}

void Unit::has_moved()
{
    an_sprite.sprite_y = 0;
    an_sprite.swap_interval = 0.3f; // sec
    currentTargetPosition = {0, 0};
    isMoving = false;
    IsAnyUnitMoving = false;
    firstFrame = true;
}

void Unit::draw(RenderWindow& window)
{
	an_sprite.draw(window);
}

void Unit::update()
{
    an_sprite.update();

    if (isMoving)
    {
		hasSomeActionBeenStared = true;
        if (firstFrame)
        {
            move_clock.restart();
            firstFrame = false;
        }

        Vector2f currentPosition = an_sprite.sprite->getPosition();
        if (currentTargetPosition == currentPosition)
            targetRoute.pop_back();

        if (targetRoute.empty())
            has_moved();
        else
        {
            currentTargetPosition = targetRoute.back()->shape.getPosition();
            if (name == "Boss")
                currentTargetPosition += BOSS_MOVE_OFFSET + BOSS_OFFSET + sf::Vector2f{96, 0};
            else
                currentTargetPosition += this->type == 0 ? DEFAULT_OFFSET: DEFAULT_OFFSET + ENEMY_OFFSET;

            Vector2f direction = currentTargetPosition - currentPosition;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            Vector2f normalizedDirection = direction / distance;

            float step = move_speed * move_clock.restart().asSeconds();
            Vector2f movement = normalizedDirection * step;

            // Ensure we don't overshoot the target
            if (distance < step)
            {
                movement = direction;
            }

            Vector2f currFramePos = currentPosition + movement;

            an_sprite.sprite->setPosition(currFramePos);
        }
    }
}

std::vector<Unit*> allay_list = {
    new Unit("Ike", 0, ClassType::swordsman, 19, 5, 5, 4, 6, 5, 5),
    new Unit("Mia", 0, ClassType::swordsman, 17, 5, 5, 3, 8, 6, 4), 
    new Unit("Oscar", 0, ClassType::warrior, 21, 5, 6, 5, 5, 5, 3), 
    new Unit("Boyd", 0, ClassType::warrior, 23, 5, 7, 4, 4, 4, 2),  
    new Unit("Rhys", 0, ClassType::soldier, 14, 5, 3, 2, 3, 5, 6),  
    new Unit("Soren", 0, ClassType::soldier, 15, 5, 4, 3, 4, 6, 5)  
};

std::vector<Unit*> enemy_list = {
    new Unit("Boss", 1, ClassType::warrior, 24, 5, 8, 4, 4, 3, 3), 
    new Unit("Sold1", 1, ClassType::soldier, 15, 5, 4, 1, 3, 3, 4),
    new Unit("Sold2", 1, ClassType::soldier, 15, 5, 3, 2, 3, 3, 4),
    new Unit("Sold3", 1, ClassType::soldier, 15, 5, 3, 2, 3, 3, 4),
    new Unit("Sold4", 1, ClassType::soldier, 15, 5, 3, 1, 3, 3, 4),
    new Unit("Sword1", 1, ClassType::swordsman, 15, 5, 3, 2, 5, 3, 4), 
    new Unit("Sword2", 1, ClassType::swordsman, 15, 5, 4, 2, 4, 3, 4),
    new Unit("Sword3", 1, ClassType::swordsman, 15, 5, 4, 2, 3, 3, 4),
    new Unit("Sword4", 1, ClassType::swordsman, 15, 5, 4, 2, 3, 3, 4),
    new Unit("Warr1", 1, ClassType::warrior, 17, 5, 5, 4, 3, 3, 3), 
    new Unit("Warr2", 1, ClassType::warrior, 17, 5, 5, 4, 2, 3, 3),
    new Unit("Warr3", 1, ClassType::warrior, 17, 5, 5, 3, 3, 3, 3)
};

