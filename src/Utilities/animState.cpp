#include "../headers/animState.h"
#include "../headers/unit.h"

sf::Texture texture;
std::string path1;
std::string path2;

AnimState::AnimState(Unit* unit) : unit(unit)
{
    if (unit->type == 0) { // Alleati
        path1 = "resources/Units/0/";
        switch (unit->unit_class) {
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
        switch (unit->unit_class) {
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
    unit->set_sprite(texture);
}

void IdleState::on_enter() {
    unit->an_sprite.sprite_y = 0;
    unit->an_sprite.update();
}

void MoveState::on_enter() {
    unit->an_sprite.sprite_y = 1; 
    unit->an_sprite.update();
}

void AttackState::on_enter() {
    unit->an_sprite.sprite_y = 2; 
    unit->an_sprite.update();
}

void DeathState::on_enter() {
    unit->an_sprite.sprite_y = 3;
    unit->an_sprite.update();
}
