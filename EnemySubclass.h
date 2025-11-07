#ifndef ENREMY_SUBCLASS_H
#define ENREMY_SUBCLASS_H
#include "EnemyClass.h"

class spawnManager;

class warrior : public enemy{
	spawnManager* spawner;
public:
	warrior(spawnManager* sm, float _x, float _y, std::string filename);
};
class rouge : public enemy {
	spawnManager* spawner;
public:
	rouge(spawnManager* sm, float _x, float _y, std::string filename);
};
class ranger : public enemy {
	spawnManager* spawner;
public:
	ranger(spawnManager* sm, float _x, float _y, std::string filename);
	void attack(float _x, float _y, float dt, float px, float py);

};
class mage : public enemy {
	spawnManager* spawner;
public:
	mage(spawnManager* sm, float _x, float _y, std::string filename);
	void attack(float _x, float _y, float dt, float px, float py);
};

#endif