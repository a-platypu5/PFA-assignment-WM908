#ifndef PLAYER_ATTACK_CLASS_H
#define PLAYER_ATTACK_CLASS_H
#include "HeroClass.h"

class pattack : public entity {
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
public:
    pattack(float _x, float _y, float _tx, float _ty, std::string filename, int damage);

    void update(GamesEngineeringBase::Window& canvas, float xmove, float ymove, float dt);
    int getAttackDamage();
};

#endif