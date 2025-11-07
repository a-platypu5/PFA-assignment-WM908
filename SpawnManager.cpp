#include <iostream>
#include "SpawnManager.h"


struct position {
    int x;
    int y;
};

//spawns enemies on the map, outside an area around the player
void spawnManager::spawnEnemy(GamesEngineeringBase::Window& canvas, hero& player, float dt) {
    if (currentSizeE < maxEnemies) {
        if (timeElapsed > spawnThreshold) { // now zonal spawning outside canvas
            int area = rand() % 4;
            position min{ 0, 0 };
            position max{ canvas.getWidth(), canvas.getHeight()};
            float x, y;
            switch (area) {
            case 0: min.y = -100; max.y = 0; break;
            case 1: min.x = canvas.getWidth(); max.x = canvas.getWidth() + 100; break;
            case 2: min.y = canvas.getHeight(); max.y = canvas.getHeight() + 100; break;
            case 3: min.x = -100; max.x = 0; break;
            }

            x = rand() % (abs(max.x - min.x)) + min.x;
            y = rand() % (abs(max.y - min.y)) + min.y;

            int subclass = rand() % 4;
            float px = player.getX();
            float py = player.getY();
            switch (subclass) {
            case 0: earray[currentSizeE++] = new warrior(this, x, y, "Resources/Enemy1.png"); break;
            case 1: earray[currentSizeE++] = new rouge(this, x, y, "Resources/Enemy2.png"); break;
            case 2: earray[currentSizeE++] = new ranger(this, x, y, "Resources/Enemy3.png"); break;
            case 3: earray[currentSizeE++] = new mage(this, x, y, "Resources/Enemy4.png"); break;
            }

            timeElapsed = 0.f;
            spawnThreshold -= 0.2f;
            spawnThreshold = max(spawnThreshold, 0.5f);
        }
    }
}

    //makes sure enemy exists before removing if player crashed
void spawnManager::checkDeleteEnemy(GamesEngineeringBase::Window& canvas, hero& player, int i) {
    if (earray[i]->collision(player)) {
        player.takeDamage(earray[i]->getDamage());
        delete earray[i];
        earray[i] = nullptr;
        shiftEnemyArray(i);
        std::cout << "Player damaged, current health: " << player.getHealth() << std::endl;
    }
}

void spawnManager::spawnPlayerProjectile(GamesEngineeringBase::Window& canvas, hero& player, int targetIndex) {
    if (currentSizeA < maxProjectiles)
        if (attackElapsed > attackDelay) {
            float x = player.getX();
            float y = player.getY();
            float ex = 0;
            float ey = 0;
            //std::cout << "closest target index: " << targetIndex << std::endl;
            if (targetIndex != -1 && earray[targetIndex]) { // making sure target still exists during spawning of projectile
                ex = earray[targetIndex]->getX();
                ey = earray[targetIndex]->getY();
                //aarray[currentSizeA++] = new attack(x, y, ex, ey, "shuriken", 35);//player damage = 35
            }
            attackElapsed = 0;
        }
    //std::cout << currentSizeA << std::endl;
}



//makes sure the player doesnt run out of shots
void spawnManager::shiftProjectileArray(int pI) {
    for (int i = pI; i < currentSizeA - 1; i++) {
        aarray[i] = aarray[i + 1];
    }
    currentSizeA--;
}
//shifts enemies, so the continue spawning until 1000 on screen
void spawnManager::shiftEnemyArray(int eI) {
    for (int i = eI; i < currentSizeE - 1; i++) {
        earray[i] = earray[i + 1];
    }
    currentSizeE--;
}

void spawnManager::shiftEPArray(int epI) {
    for (int i = epI; i < currentSizeEP - 1; i++) {
        eparray[i] = eparray[i + 1];
    }
    currentSizeEP--;
}

void spawnManager::checkDeletePlayerProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex) {
    //if collision with any enemy - damage enemy and delete projectile
    for(int i = 0; i < currentSizeE; i++)
        if (aarray[projectileIndex]->collision(*earray[i])) {
            int damage = aarray[projectileIndex]->getAttackDamage();
            earray[i]->takeDamage(damage);

            //std::cout << "enemy damaged" << std::endl;
            if (earray[i]->getHealth() <= 0) {
                player.addScore(earray[i]->getScore());//add score of each enemy killed to total on player class
                delete earray[i];
                earray[i] = nullptr;
                shiftEnemyArray(i);
            }
            delete aarray[projectileIndex];
            aarray[projectileIndex] = nullptr;
            shiftProjectileArray(projectileIndex);
            break;
        }
}

void spawnManager::checkDeleteEnemyProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex) {
    //if collision with any enemy - damage enemy and delete projectile
    for (int i = 0; i < currentSizeEP; i++)
        if (eparray[projectileIndex]->collision(player)) {
            int damage = eparray[projectileIndex]->getAttackDamage();
            player.takeDamage(damage);

            delete eparray[projectileIndex];
            eparray[projectileIndex] = nullptr;
            shiftEPArray(projectileIndex);
            break;
        }
}

//checks if projectiles leave canvas and deletes if they do
void spawnManager::checkProjectileRange(GamesEngineeringBase::Window& canvas, int projectileIndex) {
    if (aarray[projectileIndex]) {
        if (aarray[projectileIndex]->getX() > canvas.getWidth() || aarray[projectileIndex]->getX() < 0
            || aarray[projectileIndex]->getY() > canvas.getHeight() || aarray[projectileIndex]->getY() < 0) {
            delete aarray[projectileIndex];
            aarray[projectileIndex] = nullptr;
            shiftProjectileArray(projectileIndex);
        }
    }
    if (eparray[projectileIndex]) {
        if (eparray[projectileIndex]->getX() > canvas.getWidth() || eparray[projectileIndex]->getX() < 0
            || eparray[projectileIndex]->getY() > canvas.getHeight() || eparray[projectileIndex]->getY() < 0) {
            delete eparray[projectileIndex];
            eparray[projectileIndex] = nullptr;
            shiftEPArray(projectileIndex);
        }
    }
}

spawnManager::spawnManager()//smallest distance is for tracking the closest enemy target to shoot at
    : timeElapsed(0), spawnThreshold(3.0f), currentSizeE(0), attackElapsed(0),
    attackDelay(0.5f), currentSizeA(0), smallestDistance(4e5), closestIndex(-1), currentSizeEP(0) {
}

spawnManager::~spawnManager() {
    for (unsigned int i = 0; i < currentSizeE; i++) {
        if (earray[i])
            delete earray[i];
    }
    for (unsigned int j = 0; j < currentSizeA; j++) {
        if (aarray[j])
            delete aarray[j];
    }
    for (unsigned int k = 0; k < currentSizeEP; k++) {
        if (eparray[k])
            delete eparray[k];
    }
}

void spawnManager::spawnEnemyProjectiles(float _x, float _y, float px, float py, std::string type, int damage) {
    if (currentSizeEP < maxProjectiles) {
        eparray[currentSizeEP++] = new attack(_x, _y, px, py, type, damage);
    }
}

    //calls enemy update and deletion
void spawnManager::update(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove) {
    timeElapsed += dt;
    float px = player.getX();
    float py = player.getY();
    attackElapsed += dt;
    for (int i = 0; i < currentSizeE; i++) {
        if (earray[i]) {
            float dx = earray[i]->getX() - px;
            float dy = earray[i]->getY() - py;
            float dis2 = dx * dx + dy * dy;

            if (dis2 < smallestDistance) {
                smallestDistance = dis2;
                closestIndex = i;
            }
            earray[i]->update(player, xmove, ymove, dt);
            checkDeleteEnemy(canvas, player, i);
        }
    }
    smallestDistance = 4e5; // reset smallest distance to always detect new one each projectile
    for (int i = 0; i < currentSizeEP; i++) {
        if (eparray[i]) {
            eparray[i]->update(canvas, xmove, ymove, dt);
            checkDeleteEnemyProjectile(canvas, player, i);
        }
    }
    for (int i = 0; i < currentSizeA; i++) {
        if (aarray[i]) {
            aarray[i]->update(canvas, xmove, ymove, dt);
            checkDeletePlayerProjectile(canvas, player,  i);
        }
    }
    spawnPlayerProjectile(canvas, player, closestIndex);
    spawnEnemy(canvas, player, dt);
}

void spawnManager::draw(GamesEngineeringBase::Window& canvas) {
    for (unsigned int i = 0; i < currentSizeE; i++)
        if (earray[i])
            earray[i]->draw(canvas);
    for (unsigned int i = 0; i < currentSizeA; i++)
        if (aarray[i]) {
            aarray[i]->draw(canvas);
        }
    for (unsigned int i = 0; i < currentSizeEP; i++)
        if (eparray[i]) {
            eparray[i]->draw(canvas);
        }

}

