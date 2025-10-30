#ifndef TILE_H
#define TILE_H
#include "GamesEngineeringBase.h"

class tile {
    GamesEngineeringBase::Image image;
public:
    tile();
    void load(std::string filename);
    void draw(GamesEngineeringBase::Window& canvas, int y, int x);

    unsigned int getHeight();
    unsigned int getWidth();
    GamesEngineeringBase::Image& getSprite();
};

#endif