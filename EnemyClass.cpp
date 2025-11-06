#include <string>
#include "EnemyClass.h"


enemy::enemy(float _x, float _y, std::string filename) : entity(_x, _y, filename) {
    speed = 0;
    health = 50;
    score = 10;
    attackRange = 0;
    attackDamage = 10;
    attackDelay = 1;
    attackElapsed = 0;
}

    //moves the enemy toward the player, but takes into account virtual player movement
void enemy::update(hero& player, float xmove, float ymove, float dt) {
    float px = player.getX();
    float py = player.getY();
    attackElapsed += dt;
    if (x > px + attackRange + 20)//+- 20 avoids enemies flickering at higher speeds, and adds an area enemies target
        x -= speed * dt;
    else if (x < px - attackRange - 20)
        x += speed * dt;
    if (y > py + attackRange + 20)
        y -= speed * dt;
    else if (y < py - attackRange - 20)
        y += speed * dt;

    // changes movement of enemies when player moves away
    if (xmove != 0)
        x += xmove * dt; 
    if (ymove != 0)
        y += ymove * dt;

}

void enemy::takeDamage(int damage) {
    health -= damage;
}

int enemy::getHealth() { return health; }
int enemy::getScore() { return score; }
