#include <iostream>
#include "SpawnManager.h"



    //spawns enemies on the map, outside an area around the player
void spawnManager::spawnEnemy(GamesEngineeringBase::Window& canvas, hero& player) {
    if (currentSizeE < maxEnemies) {
        if (timeElapsed > spawnThreshold) {
            int rx = rand() % canvas.getWidth();//mapx max
            int ry = rand() % canvas.getHeight();//mapy max
            int x;
            int y;
            int safeRange= 250;

            //need to use a get funciton as the x, y is protected/private
            int px = player.getX();
            int py = player.getY();

            //cout << rx << '\t' << ry << endl;
            if (abs(rx - px) > safeRange || abs(ry - py) > safeRange) {
                x = rx;
                y = ry;
            }
            //randomly move enemy to an edge of the safe spawn area if initially inside
            else {
                bool coin = rand() % 2;
                if (coin) {
                    x = (rand() % 2 == 0 ? px + safeRange : px - safeRange);
                    y = ry;
                }
                else {
                    x = rx;
                    y = (rand() % 2 == 0 ? py + safeRange : py - safeRange);
                }
            }

            //cout << x << '\t' << y<< endl;
            //spawns enemy in heap array on an decreasing time interval to a min of 0.5f
            earray[currentSizeE++] = new enemy(x, y, "Resources/L2.png");
            timeElapsed = 0.f;
            spawnThreshold -= 0.2f;
            spawnThreshold = max(spawnThreshold, 0.5f);
        }
    }
}

    //makes sure enemy exists before removing if player crashed
void spawnManager::checkDeleteEnemy(GamesEngineeringBase::Window& canvas, hero& player, int i) {
    if (earray[i]->collision(player)) {
        delete earray[i];
        earray[i] = nullptr;
        std::cout << "player damaged" << std::endl;
    }
}

void spawnManager::spawnProjectile(GamesEngineeringBase::Window& canvas, hero& player, int targetIndex) {
    if (currentSizeA < maxProjectiles)
        if (attackElapsed > attackDelay) {
            int x = player.getX();
            int y = player.getY();
            int ex = 0;
            int ey = 0;
            //std::cout << "closest target index: " << targetIndex << std::endl;
            if (targetIndex != -1 && earray[targetIndex]) { // making sure target still exists during spawning of projectile
                ex = earray[targetIndex]->getX();
                ey = earray[targetIndex]->getY();
                aarray[currentSizeA++] = new pattack(x, y, ex, ey, "Resources/shuriken0.png");
            }
            attackElapsed = 0;
        }
}

void spawnManager::checkDeleteProjectile(GamesEngineeringBase::Window& canvas, hero& player, int projectileIndex) {
    //if collision with any enemy - delete enemy and projectile
    for(int i = 0; i < currentSizeE; i++)
        if (aarray[projectileIndex]->collision(*earray[i])) {
            delete aarray[projectileIndex];
            aarray[projectileIndex] = nullptr;
            std::cout << "enemy damaged" << std::endl;
            delete earray[i];
            earray[i] = nullptr;
            break;
        }
    if (aarray[projectileIndex]) {
        if (aarray[projectileIndex]->getX() > canvas.getWidth() || aarray[projectileIndex]->getX() < 0
            || aarray[projectileIndex]->getY() > canvas.getHeight() || aarray[projectileIndex]->getY() < 0) {
            delete aarray[projectileIndex];
            aarray[projectileIndex] = nullptr;
        }
    }
}

spawnManager::spawnManager()
    : timeElapsed(0), spawnThreshold(3.0f), currentSizeE(0), attackElapsed(0),
    attackDelay(0.5f), currentSizeA(0), smallestDistance(4e5), closestIndex(-1) {
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
}

    //calls enemy update and deletion
void spawnManager::update(GamesEngineeringBase::Window& canvas, hero& player, float dt, int xmove, int ymove) {
    timeElapsed += dt;
    attackElapsed += dt;
    for (int i = 0; i < currentSizeE; i++) {
        if (earray[i]) {
            float dx = earray[i]->getX() - player.getX();
            float dy = earray[i]->getY() - player.getY();
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
    for (int i = 0; i < currentSizeA; i++) {
        if (aarray[i]) {
            aarray[i]->update(canvas, player, xmove, ymove, dt);
            checkDeleteProjectile(canvas, player,  i);
        }
    }
    spawnProjectile(canvas, player, closestIndex);
    spawnEnemy(canvas, player);
}

void spawnManager::draw(GamesEngineeringBase::Window& canvas) {
    for (unsigned int i = 0; i < currentSizeE; i++)
        if (earray[i])
            earray[i]->draw(canvas);
    for (unsigned int i = 0; i < currentSizeA; i++)
        if (aarray[i]) {
            aarray[i]->draw(canvas);
        }
}

