#include <iostream>
#include "EnemySubclass.h"

warrior::warrior(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 200;
	health = 100;
}

rouge::rouge(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 300;
	health = 50;
}

ranger::ranger(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 100;
	health = 50;
}

mage::mage(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 50;
	health = 25;
}
