#pragma once
#include <string>
#include <optional>
#include "animatedSprite.h"
#include "weapon.h"

class Tile;

static float UNITS_SPEED = 170.0f;
static float SWAP_INTERVAL = 0.3f;
static float SWAP_INTERVAL_RUN = 0.1f;

enum ClassType
{
    swordsman = 0,
    warrior = 1,
    soldier = 2,
};

class Unit {
public:
    std::string name;
    int type; // 0 allay, 1 enemy
    bool canMove;
    ClassType unit_class;
    std::optional<Weapon> equiped_weapon;
    bool unguento = true;
    AnimatedSprite an_sprite;

    sf::Vector2f currentTargetPosition; // Posizione di destinazione
    std::vector<Tile*> targetRoute; // Percorso da seguire
	bool firstFrame = true; // Flag per il primo frame di movimento;
    bool isMoving = false;
    bool move_just_started = false;
    static float move_speed; // Speed in pixels per second
    sf::Clock move_clock; // Clock for movement timing

    static bool IsAnyUnitMoving;
    static bool hasSomeActionBeenStared;

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
    Unit(std::string n, bool t, ClassType c, int mh, int mv, int str, int def, int spe, int skl, int lck);
    Weapon initialize_weapon(ClassType c) const;
    sf::Texture load_texture(int type, ClassType unit_class) const;

    void set_sprite(sf::Texture t);
    void set_sprite_pos(sf::Vector2i coord);
    void has_moved();

    int get_dodge() const;
    int get_hit() const;
    int get_attack() const;
    int get_crit() const;

    void draw(sf::RenderWindow& window);
    void update();
};

//in modo che non vengano ridefinite, senza, i puntatori cambiano di valore
extern std::vector<Unit*> allay_list;
extern std::vector<Unit*> enemy_list;

constexpr sf::Vector2f BOSS_OFFSET(-16, -21);
constexpr sf::Vector2f BOSS_MOVE_OFFSET(-11, -11);
constexpr sf::Vector2f DEFAULT_OFFSET(-12, -12);
constexpr sf::Vector2f ENEMY_OFFSET(63, 0);



