#ifndef PLAYER_ATTACK_CLASS_H
#define PLAYER_ATTACK_CLASS_H
#include "HeroClass.h"

class pattack : public entity {
    int n;
    int frameTimer;
    int speed;
    int px, py;
    int ex, ey;
    int dx;
    int dy;
    float dirX;
    float dirY;
public:
    pattack(int _x, int _y, int _ex, int _ey, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, hero& player, int xmove, int ymove, float dt);
};

#endif