#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "GamesEngineeringBase.h"

void drawCircle(GamesEngineeringBase::Window& canvas, int cx, int cy, int radius);

class entity {
protected:
    int x;
    int y;
    float radius;
    GamesEngineeringBase::Image image;
public:
    entity(int _x, int _y, std::string filename);

    float getX();
    float getY();
    //draws sprites & collision circle
    void draw(GamesEngineeringBase::Window& canvas);
    void drawCentre(GamesEngineeringBase::Window& canvas);

    bool collision(entity& e);
};

#endif