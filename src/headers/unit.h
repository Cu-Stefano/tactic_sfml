#include <string>

enum ClassType
{
	spadaccino = 0,
	guerriero = 1,
	soldato = 2,
};

struct Unit {

	std::string name;
	bool type; // 0 alleati, 1 nemici
	ClassType unit_class;

	int hp;
	int max_hp;
	int strength;
	int defense;
	int speed;
	int skill;

	int Get_Dodge();
	int Get_Hit();
	int Get_Attack();
	int Get_Crit();

};