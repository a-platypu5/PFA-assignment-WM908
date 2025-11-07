#include <iostream>
#include "HeroClass.h"

hero::hero(float _x, float _y, std::string filename) : entity(_x, _y, filename) {
    health = 1000;
    speed = 300;
    totalScore = 0;
}

void hero::update(GamesEngineeringBase::Window& canvas, float _x, float _y) {
    x = _x;
    y = _y;
}

int hero::getHealth() { return health; }
int hero::getSpeed() { return speed; }
int hero::getScore() { return totalScore; }
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