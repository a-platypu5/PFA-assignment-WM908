#include <iostream>
#include "HeroClass.h"

hero::hero(float _x, float _y, std::string filename) : entity(_x, _y, filename) {}

void hero::update(GamesEngineeringBase::Window& canvas, float _x, float _y) {
    x = _x;
    y = _y;
}
