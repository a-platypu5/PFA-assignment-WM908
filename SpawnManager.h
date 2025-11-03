#ifndef SPAWN_MANAGER
#define SPAWN_MANAGER
#include "HeroClass.h"
#include "EnemyClass.h"
#include "PlayerAttackClass.h"

const unsigned int maxEnemies = 1000;
const unsigned int maxProjectiles = 100; //currently 100 max shots used, rather than on screen
// possibly using stack and queue method to create a looping array

class spawnManager {
    enemy* earray[maxEnemies];
    pattack* aarray[maxProjectiles];
    float timeElapsed;
    float spawnThreshold;
    int currentSizeE;
    float attackElapsed;
    float attackDelay;
    int currentSizeA;
    float smallestDistance;
    int closestIndex;

    //spawns enemies on the map, outside an area around the player
    void spawnEnemy(GamesEngineeringBase::Window& canvas, hero& player);

    //makes sure enemy exists before removing if player crashed
    void checkDeleteEnemy(GamesEngineeringBase::Window& canvas, hero& player, int i);

    void spawnProjectile(GamesEngineeringBase::Window& canvas, hero& player, int targetIndex);

    void checkDeleteProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex);

public:
    spawnManager();

    ~spawnManager();

    //calls enemy update and deletion
    void update(GamesEngineeringBase::Window& canvas, hero& player, float dt, int xmove, int ymove);

    void draw(GamesEngineeringBase::Window& canvas);

};

#endif
