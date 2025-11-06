#ifndef ENREMY_SUBCLASS_H
#define ENREMY_SUBCLASS_H
#include "EnemyClass.h"

class spawnManager;

class warrior : public enemy{
	spawnManager* spawner;
public:
	warrior(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt);
};
class rouge : public enemy {
	spawnManager* spawner;
public:
	rouge(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt);
};
class ranger : public enemy {
	spawnManager* spawner;
public:
	ranger(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt);
	//void attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove);

};
class mage : public enemy {
	spawnManager* spawner;
public:
	mage(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt);
	void attack(float dt, float px, float py);
};

#endif