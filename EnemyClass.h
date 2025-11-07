#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H
#include "HeroClass.h"
#include "EntityClass.h"

class enemy : public entity {
protected:
    int speed;
    int health;
    int score;
    int attackRange;
    int attackDamage;
    float attackDelay;
    float attackElapsed;
    std::string type;
public:
    enemy(float _x, float _y, std::string filename);

    //moves the enemy toward the player, but takes into account virtual player movement
    void update(hero& player, float xmove, float ymove, float dt);

    virtual void attack(float _x, float _y, float dt, float px, float py);

    void takeDamage(int damage);
    int getHealth();
    int getScore();
    int getDamage();
};

#endif