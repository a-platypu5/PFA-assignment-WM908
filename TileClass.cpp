#include <iostream>
#include "TileClass.h"

tile::tile() {}
void tile::load(std::string filename) {
    image.load(filename);
}
void tile::draw(GamesEngineeringBase::Window& canvas, int x, int y) {
    for (unsigned int i = 0; i < image.height; i++)
        if (y + i > 0 && (y + i) < (canvas.getHeight()))
            for (unsigned int n = 0; n < image.width; n++)
                if (x + n > 0 && (x + n) < (canvas.getWidth()))
                    canvas.draw(x + n, y + i, image.atUnchecked(n, i));
}
unsigned int tile::getHeight() { return 32; }
unsigned int tile::getWidth() { return 32; }
GamesEngineeringBase::Image& tile::getSprite() { return image; }
