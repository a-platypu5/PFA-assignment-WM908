#include <string>
#include <cmath>
#include "AttackClass.h"


attack::attack(float _x, float _y, float _tx, float _ty, std::string type, int damage, float duration)
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
    attackDuration = duration;
    durationEnded = false;
}

void attack::update(GamesEngineeringBase::Window& canvas, float xmove, float ymove, float dt) {
    //target and move towards closest enemy x, y coords
    //keep target even if new target aquired.
    attackDuration -= dt;
    frameTimer++;
    if (frameTimer >= 5) {
        frameTimer = 0;
        n++;
        if (n >= 8)
            n = 0;
    }
   //image.load("Resources/" + entityType + std::to_string(n) + ".png"); //scrolls through 8 .png TANKS THE FPS
    if (entityType != "aoe") {
        x += dirX * speed * dt;
        y += dirY * speed * dt;
    }
    x += xmove * dt;
    y += ymove * dt;
    
    if (attackDuration <= 0 && entityType == "aoe") {
        durationEnded = true;
    }
}

bool attack::hasDurationEnded() { return durationEnded; }
int attack::getAttackDamage() { return attackDamage; }
