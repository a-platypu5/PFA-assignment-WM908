#include <string>
#include <cmath>
#include "PlayerAttackClass.h"


pattack::pattack(int _x, int _y, int _ex, int _ey, std::string filename)
    : entity(_x, _y, filename), n(0), frameTimer(0), speed(8), dirX(0), dirY(0) {
    px = _x;
    py = _y;
    ex = _ex;
    ey = _ey;
    dx = (ex - px);
    dy = (ey - py);
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        dirX = dx / length;
        dirY = dy / length;
    }
}

void pattack::update(GamesEngineeringBase::Window& canvas, hero& player, int xmove, int ymove) {
    //target and move towards closest enemy x, y coords
    //keep target even if new target aquired.
    frameTimer++;
    if (frameTimer >= 5) {
        frameTimer = 0;
        n++;
        if (n >= 8)
            n = 0;
    }
    image.load("Resources/shuriken" + std::to_string(n) + ".png"); //scrolls through 8 .png

    x += dirX * speed;
    y += dirY * speed;

    if (xmove != 0)
        x += xmove; // changes movement of enemies when player moves away
    if (ymove != 0)
        y += ymove;
    if (x < 0 || x > canvas.getWidth() || y < 0 || y > canvas.getHeight()) {
        //delete projectile
    }
}
