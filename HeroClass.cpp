#include <iostream>
#include "HeroClass.h"
#include "SpawnManager.h"

hero::hero(spawnManager* sm, float _x, float _y, std::string filename) : entity(_x, _y, filename), spawner(sm) {
    health = 1000;
    speed = 300;
    totalScore = 0;
    damage = 35;
    aoeDamage = 100; //damage over time
    aoeDelay = 10.0f;
    aoeElapsed = 0;
    aoeDuration = 2.0f;
    type = "aoe";
}

void hero::update(GamesEngineeringBase::Window& canvas, float _x, float _y) {
    x = _x;
    y = _y;
}

void hero::aoeAttack(GamesEngineeringBase::Window& canvas, float dt) {
    if (aoeElapsed > aoeDelay) {
        spawner->spawnAOEProjectile(canvas, aoeDamage, aoeDuration, type, dt);
        aoeElapsed = 0;
    }
}

int hero::getHealth() { return health; }
int hero::getSpeed() { return speed; }
int hero::getScore() { return totalScore; }
int hero::getDamage() { return damage; }
void hero::addScore(int score) {
    totalScore += score;
}
void hero::takeDamage(int damage) {
    if (health >= (0 + damage)) {
        health -= damage;
    }
    else {
        health = 0;
        std::cout << "PLAYER DIED" << std::endl;
    }
}
void hero::increaseTime(float dt) {
    aoeElapsed += dt;
}
void hero::setGodHealth() {
    health = 10000;
}