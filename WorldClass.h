#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H
#include "TileSetClass.h"

const unsigned int worldSizeX = 100;
const unsigned int worldSizeY = 100;
class world {
    tileSet ts;
    unsigned int tarray[worldSizeY][worldSizeX];
    int LEFT;
    int ABOVE;
    float baseWeights[tileNum];
public:
    world();
    int getWeightedTile(const float weights[tileNum]);
    int pickTileFromWeight(int indexi, int indexj);
    void draw(GamesEngineeringBase::Window& canvas, int _x, int _y);
    void print();
};

#endif