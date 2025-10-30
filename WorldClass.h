#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H
#include "GamesEngineeringBase.h"
#include "TileClass.h"
#include "TileSetClass.h"

const unsigned int worldSize = 1024;
class world {
    tileSet ts;
    unsigned int tarray[worldSize];
    int LEFT;
    int ABOVE;
    float baseWeights[tileNum];
public:
    world();
    int getWeightedTile(const float weights[tileNum]);
    int pickTileFromWeight(int index);
    void draw(GamesEngineeringBase::Window& canvas, int _x, int _y);
    void print();
};

#endif