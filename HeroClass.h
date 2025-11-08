#ifndef HERO_CLASS_H
#define HERO_CLASS_H
#include "EntityClass.h"

class spawnManager;

class hero : public entity {
    int health;
    int speed;
    int totalScore;
    int damage;
    int aoeDamage;
    spawnManager* spawner;
    float aoeDelay;
    float aoeElapsed;
    float aoeDuration;
    std::string type;
public:
    hero(spawnManager* sm, float _x, float _y, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, float _x, float _y);

    void aoeAttack(GamesEngineeringBase::Window& canvas, float dt);

    int getHealth();
    int getSpeed();
    int getScore();
    void addScore(int score);
    void takeDamage(int damage);
    int getDamage();
    void increaseTime(float dt);
    void setGodHealth();
};

#endif