#include <string>
#include "EnemyClass.h"


enemy::enemy(int _x, int _y, std::string filename) : entity(_x, _y, filename), speed(3) {
}

    //moves the enemy toward the player, but takes into account virtual player movement
void enemy::update(hero& player, int xmove, int ymove) {
    int px = player.getX();
    int py = player.getY();
    if (x > px + 20)//+- 20 avoids enemies flicxkering at higher speeds, and adds an area enemies target
        x -= speed;
    else if (x < px - 20)
        x += speed;
    if (y > py + 20)
        y -= speed;
    else if (y < py - 20)
        y += speed;
    if (xmove != 0)
        x += xmove; // changes movement of enemies when player moves away
    if (ymove != 0)
        y += ymove;
}
