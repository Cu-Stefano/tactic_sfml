enum WeaponType
{
    sword,
    axe,
    lance,
};

class Weapon
{
public:
    int range;
    int damage;
    int hit;
    int critical;
    WeaponType type;

    Weapon(int r, int d, int h, int c, WeaponType w);
};