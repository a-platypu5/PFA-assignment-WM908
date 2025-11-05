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
};
class mage : public enemy {
public:
	mage(float _x, float _y, std::string filename);
};

#endif