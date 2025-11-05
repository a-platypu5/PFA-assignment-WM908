#ifndef HERO_CLASS_H
#define HERO_CLASS_H
#include "EntityClass.h"

class hero : public entity {
public:
    hero(float _x, float _y, std::string filename);

    void update(GamesEngineeringBase::Window& canvas, float _x, float _y);
};

#endif