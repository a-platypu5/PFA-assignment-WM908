#ifndef ATTACK_CLASS_H
#define ATTACK_CLASS_H
#include "HeroClass.h"

class attack : public entity {
    int n;
    int frameTimer;
    int speed;
    float ox, oy;
    float tx, ty;
    int dx;
    int dy;
    float dirX;
    float dirY;
    int attackDamage;
    std::string entityType;
    float attackDuration;
    bool durationEnded;
public:
    attack(float _x, float _y, float _tx, float _ty, std::string filename, int damage, float duration);

    void update(GamesEngineeringBase::Window& canvas, float xmove, float ymove, float dt);

    bool hasDurationEnded();
    int getAttackDamage();
};

#endif