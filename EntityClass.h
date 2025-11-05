#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "GamesEngineeringBase.h"

void drawCircle(GamesEngineeringBase::Window& canvas, float cx, float cy, int radius);

class entity {
protected:
    float x;
    float y;
    float radius;
    GamesEngineeringBase::Image image;
public:
    entity(float _x, float _y, std::string filename);

    float getX();
    float getY();
    //draws sprites & collision circle
    void draw(GamesEngineeringBase::Window& canvas);
    void drawCentre(GamesEngineeringBase::Window& canvas);

    bool collision(entity& e);
};

#endif