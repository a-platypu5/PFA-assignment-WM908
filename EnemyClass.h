#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H
#include "HeroClass.h"

class enemy : public entity {
    int speed;
public:
    enemy(int _x, int _y, std::string filename);

    //moves the enemy toward the player, but takes into account virtual player movement
    void update(hero& player, int xmove, int ymove);
};

#endif