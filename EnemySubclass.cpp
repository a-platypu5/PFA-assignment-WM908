#include <iostream>
#include "EnemySubclass.h"
#include "SpawnManager.h"

warrior::warrior(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt) : enemy(_x, _y, filename), spawner(sm) {
	speed = 200;
	health = 100;
	score = 10;
	attackRange = 0;
	attackDamage = 30;
	attackDelay = 0.5f;
}

rouge::rouge(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt) : enemy(_x, _y, filename), spawner(sm) {
	speed = 300;
	health = 50;
	score = 10;
	attackRange = 0;
	attackDamage = 15;
	attackDelay = 0.2f;
}

ranger::ranger(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt) : enemy(_x, _y, filename), spawner(sm) {
	speed = 100;
	health = 50;
	score = 10;
	attackRange = 150;
	attackDamage = 20;
	attackDelay = 0.3f;
	type = "ranger";
}
//void ranger::attack(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove) {
//
//}

mage::mage(spawnManager* sm, float _x, float _y, std::string filename, float px, float py, float dt) : enemy(_x, _y, filename), spawner(sm) {
	speed = 50;
	health = 25;
	score = 10;
	attackRange = 300;
	attackDamage = 50;
	attackDelay = 0.8f;
	attackElapsed = 0;
	type = "mage";
	x = _x;
	y = _y;
	attack(dt, px, py);

}
void mage::attack(float dt, float px, float py) {
	attackElapsed += dt;
	if (attackElapsed >= attackDelay) {
		spawner->spawnEnemyProjectiles(x, y, px, py, type, attackDamage);
			attackElapsed = 0;
	}
}
