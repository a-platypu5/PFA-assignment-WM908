#include <iostream>
#include "EnemySubclass.h"

warrior::warrior(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 200;
	health = 100;
	score = 10;
	attackRange = 0;
	attackDamage = 30;
	attackDelay = 0.5f;
}

rouge::rouge(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 300;
	health = 50;
	score = 10;
	attackRange = 0;
	attackDamage = 15;
	attackDelay = 0.2f;
}

ranger::ranger(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 100;
	health = 50;
	score = 10;
	attackRange = 150;
	attackDamage = 20;
	attackDelay = 0.3f;
}
void ranger::attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove) {

}

mage::mage(float _x, float _y, std::string filename) : enemy(_x, _y, filename) {
	speed = 50;
	health = 25;
	score = 10;
	attackRange = 300;
	attackDamage = 50;
	attackDelay = 0.8f;
	attackElapsed = 0;

}
void mage::attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove) {
}
float mage::getAttackDelay() { return attackDelay; }
float mage::getTimeElapsed() { return attackElapsed; }
void mage::resetTimeElapsed() {
	attackElapsed = 0;
}
