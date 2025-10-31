#ifndef HERO_CLASS_H
#define HERO_CLASS_H
#include "EntityClass.h"

class hero : public entity {
public:
    hero(int _x, int _y, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, int _x, float _y);
};

#endif