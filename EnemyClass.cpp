#include <string>
#include "EnemyClass.h"


enemy::enemy(float _x, float _y, std::string filename) : entity(_x, _y, filename) {
    speed = 0;
    health = 50;
}

    //moves the enemy toward the player, but takes into account virtual player movement
void enemy::update(hero& player, float xmove, float ymove, float dt) {
    float px = player.getX();
    float py = player.getY();
    if (x > px + 20)//+- 20 avoids enemies flickering at higher speeds, and adds an area enemies target
        x -= speed * dt;
    else if (x < px - 20)
        x += speed * dt;
    if (y > py + 20)
        y -= speed * dt;
    else if (y < py - 20)
        y += speed * dt;
    if (xmove != 0)
        x += xmove * dt; // changes movement of enemies when player moves away
    if (ymove != 0)
        y += ymove * dt;
}

void enemy::takeDamage(int damage) {
    health -= damage;
}

int enemy::getHealth() { return health; }
