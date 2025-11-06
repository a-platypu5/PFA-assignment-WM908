#include <string>
#include <cmath>
#include "PlayerAttackClass.h"


pattack::pattack(float _x, float _y, float _tx, float _ty, std::string type, int damage)
    : entity(_x, _y, "Resources/" + type + "0.png"), n(0), frameTimer(0), speed(500), dirX(0), dirY(0), attackDamage(35) {
    ox = _x;
    oy = _y;
    tx = _tx;
    ty = _ty;
    dx = (tx - ox);
    dy = (ty - oy);
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        dirX = dx / length;
        dirY = dy / length;
    }
    attackDamage = damage;
    entityType = type;
}

void pattack::update(GamesEngineeringBase::Window& canvas, float xmove, float ymove, float dt) {
    //target and move towards closest enemy x, y coords
    //keep target even if new target aquired.
    frameTimer++;
    if (frameTimer >= 5) {
        frameTimer = 0;
        n++;
        if (n >= 8)
            n = 0;
    }
    image.load("Resources/" + entityType + std::to_string(n) + ".png"); //scrolls through 8 .png

    x += dirX * speed * dt;
    y += dirY * speed * dt;
    x += xmove * dt;
    y += ymove * dt;
}

int pattack::getAttackDamage() { return attackDamage; }
