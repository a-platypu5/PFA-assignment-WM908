#ifndef TILESET_H
#define TILESET_H
#include "TileClass.h"

const unsigned int tileNum = 5;
class tileSet {
    tile t[tileNum];
    std::string string;
public:
    tileSet(std::string pre = "");
    tile& operator[](unsigned int index);
};

#endif