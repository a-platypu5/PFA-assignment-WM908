#ifndef ENREMY_SUBCLASS_H
#define ENREMY_SUBCLASS_H
#include "EnemyClass.h"

class warrior : public enemy{
public:
	warrior(float _x, float _y, std::string filename);
};
class rouge : public enemy {
public:
	rouge(float _x, float _y, std::string filename);
};
class ranger : public enemy {
public:
	ranger(float _x, float _y, std::string filename);
	void attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove);

};
class mage : public enemy {
public:
	mage(float _x, float _y, std::string filename);
	void attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove);
	float getAttackDelay();
	float getTimeElapsed();
	void resetTimeElapsed();
};

#endif