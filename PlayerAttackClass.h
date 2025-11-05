#ifndef PLAYER_ATTACK_CLASS_H
#define PLAYER_ATTACK_CLASS_H
#include "HeroClass.h"

class pattack : public entity {
    int n;
    int frameTimer;
    int speed;
    float px, py;
    float ex, ey;
    int dx;
    int dy;
    float dirX;
    float dirY;
    int attackDamage;
public:
    pattack(float _x, float _y, float _ex, float _ey, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, hero& player, float xmove, float ymove, float dt);
    int getAttackDamage();
};

#endif