#include <string>
#include <cmath>
#include "PlayerAttackClass.h"


pattack::pattack(float _x, float _y, float _ex, float _ey, std::string filename)
    : entity(_x, _y, filename), n(0), frameTimer(0), speed(500), dirX(0), dirY(0), attackDamage(35) {
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

void pattack::update(GamesEngineeringBase::Window& canvas, hero& player, float xmove, float ymove, float dt) {
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

    x += dirX * speed * dt;
    y += dirY * speed * dt;
    x += xmove * dt;
    y += ymove * dt;
}

int pattack::getAttackDamage() { return attackDamage; }
