#ifndef SPAWN_MANAGER
#define SPAWN_MANAGER
#include "HeroClass.h"
#include "EnemySubclass.h"
#include "AttackClass.h"

const unsigned int maxEnemies = 1000;
const unsigned int maxProjectiles = 100; //currently 100 max shots used, rather than on screen
// possibly using stack and queue method to create a looping array

class spawnManager {
    enemy* earray[maxEnemies];
    attack* aarray[maxProjectiles];
    attack* eparray[maxProjectiles];
    float timeElapsed;
    float spawnThreshold;
    int currentSizeE;
    float attackElapsed;
    float attackDelay;
    int currentSizeA;
    float smallestDistance;
    int closestIndex;
    int currentSizeEP;

    //spawns enemies on the map, outside an area around the player
    void spawnEnemy(GamesEngineeringBase::Window& canvas, hero& player, float dt);

    //makes sure enemy exists before removing if player crashed
    void checkDeleteEnemy(GamesEngineeringBase::Window& canvas, hero& player, int i);

    void spawnPlayerProjectile(GamesEngineeringBase::Window& canvas, hero& player, int targetIndex);


    void shiftProjectileArray(int pi);
    void shiftEnemyArray(int ei);
    void shiftEPArray(int epi);

    void checkDeletePlayerProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex);
    void checkDeleteEnemyProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex);
    void checkProjectileRange(GamesEngineeringBase::Window& canvas, int projectileIndex);

public:
    spawnManager();

    ~spawnManager();

    void spawnEnemyProjectiles(float _x, float _y, float px, float py, std::string type, int damage);

    //calls enemy update and deletion
    void update(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove);

    void draw(GamesEngineeringBase::Window& canvas);

};

#endif
