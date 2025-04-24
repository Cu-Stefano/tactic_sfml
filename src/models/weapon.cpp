#include "../headers/weapon.h"

Weapon::Weapon(int r, int d, int h, int c, WeaponType w)
{
	range = r;
	damage = d;
	hit = h;
	critical = c;
	type = w;
}