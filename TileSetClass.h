#ifndef TILESET_H
#define TILESET_H
#include "GamesEngineeringBase.h"
#include "TileClass.h"

const unsigned int tileNum = 3;
class tileSet {
    tile t[tileNum];
    std::string string;
public:
    tileSet(std::string pre = "");
    tile& operator[](unsigned int index);
};

#endif