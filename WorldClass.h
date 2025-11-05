#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H
#include "TileSetClass.h"

const unsigned int worldSizeX = 100;
const unsigned int worldSizeY = 100;
class world {
    tileSet ts;
    unsigned int** tileMap;
    int LEFT;
    int ABOVE;
    float baseWeights[tileNum];
    int mapType;
public:
    world();
    ~world();
    int getWeightedTile(const float weights[tileNum]);
    int pickTileFromWeight(int indexi, int indexj);
    void draw(GamesEngineeringBase::Window& canvas, float _x, float _y);
    void update(float& mapx, float& mapy);
    void print();
};

#endif