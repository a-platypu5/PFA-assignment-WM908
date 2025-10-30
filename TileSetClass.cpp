#include <iostream>
#include "TileSetClass.h"
#include "TileClass.h"


    tileSet::tileSet(std::string pre) : string(pre) {
        for (unsigned int i = 0; i < tileNum; i++) {
            std::string filename;
            filename = "Resources/" + pre + std::to_string(i) + ".png";
            t[i].load(filename);
        }
    }
    tile& tileSet::operator[](unsigned int index) { return t[index]; }
