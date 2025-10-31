#include <iostream>
#include "HeroClass.h"

hero::hero(int _x, int _y, std::string filename) : entity(_x, _y, filename) {}

void hero::update(GamesEngineeringBase::Window& canvas, int _x, float _y) {
    x = _x - image.width / 2;
    y = _y - image.height / 2;
}
