#ifndef HERO_CLASS_H
#define HERO_CLASS_H
#include "EntityClass.h"

class hero : public entity {
    int health;
    int speed;
    int totalScore;
public:
    hero(float _x, float _y, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, float _x, float _y);

    int getHealth();
    int getSpeed();
    int getScore();
    void addScore(int score);
    void takeDamage(int damage);
};

#endif