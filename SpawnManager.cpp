#include <iostream>
#include "SpawnManager.h"


struct position {
    int x;
    int y;
};

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
                aarray[currentSizeA++] = new attack(x, y, ex, ey, "shuriken", player.getDamage(), 0);//0 for duration of the attack
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
    aarray[currentSizeA - 1] = nullptr;
    currentSizeA--;
}
//shifts enemies, so the continue spawning until 1000 on screen
void spawnManager::shiftEnemyArray(int eI) {
    for (int i = eI; i < currentSizeE - 1; i++) {
        earray[i] = earray[i + 1];
    }
    earray[currentSizeE - 1] = nullptr;
    currentSizeE--;
}
void spawnManager::shiftEPArray(int epI) {
    for (int i = epI; i < currentSizeEP - 1; i++) {
        eparray[i] = eparray[i + 1];
    }
    eparray[currentSizeEP - 1] = nullptr;
    currentSizeEP--;
}
void spawnManager::shiftAOEArray(int aoeI) {
    for (int i = aoeI; i < currentSizeA - 1; i++) {
        aoearray[i] = aoearray[i + 1];
    }
    eparray[currentSizeA - 1] = nullptr;
    currentSizeA--;
}

void spawnManager::checkDeletePlayerProjectile(hero& player, int projectileIndex) {
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

void spawnManager::checkDeleteEnemyProjectile(hero& player, int projectileIndex) {
    //if collision with any enemy - damage enemy and delete projectile
    if (eparray[projectileIndex]->collision(player)) {
        int damage = eparray[projectileIndex]->getAttackDamage();
        player.takeDamage(damage);
        std::cout << "Player damaged, current health: " << player.getHealth() << std::endl;

        delete eparray[projectileIndex];
        eparray[projectileIndex] = nullptr;
        shiftEPArray(projectileIndex);
    }
}

void spawnManager::deleteAOEProjectile(int projectileIndex) {
    delete aoearray[projectileIndex];
    aoearray[projectileIndex] = nullptr;
    shiftAOEArray(projectileIndex);
}

void spawnManager::checkAOECollision(hero& player, int projectileIndex, float dt) {
    int damage = aoearray[projectileIndex]->getAttackDamage();
    for (int i = 0; i < currentSizeE; i++) {
        if (aoearray[projectileIndex]->collision(*earray[i])) {
            damage *= dt;
            earray[i]->takeDamage(damage);

            if (earray[i]->getHealth() <= 0) {
                player.addScore(earray[i]->getScore());//add score of each enemy killed to total on player class
                delete earray[i];
                earray[i] = nullptr;
                shiftEnemyArray(i);
            }
        }
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
//deletes enemies outside double the camera width and height
void spawnManager::checkEnemyRange(GamesEngineeringBase::Window& canvas, int index) {
    if (earray[index]) {
        float x = earray[index]->getX();
        float y = earray[index]->getY();
        float canvasW = canvas.getWidth();
        float canvasH = canvas.getHeight();
        if (x > canvasW * 2 || x < 0 - canvasW
            || y > canvasH * 2 || y < 0 - canvasH) {
            delete earray[index];
            earray[index] = nullptr;
            shiftEnemyArray(index);
        }
    }
}

spawnManager::spawnManager()//smallest distance is for tracking the closest enemy target to shoot at
    : timeElapsed(0), spawnThreshold(1.5f), currentSizeE(0), attackElapsed(0),
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
    for (unsigned int l = 0; l < currentSizeA; l++) {
        if (aoearray[l])
            delete aoearray[l];
    }
    delete[] earray;
    delete[] aarray;
    delete[] eparray;
    delete[] aoearray;
}

void spawnManager::spawnEnemyProjectiles(float _x, float _y, float px, float py, std::string type, int damage) {
    if (currentSizeEP < maxProjectiles) {
        eparray[currentSizeEP++] = new attack(_x, _y, px, py, type, damage, 0);//0 is duration of attack, nothing for this attack
    }
}
void spawnManager::spawnAOEProjectile(GamesEngineeringBase::Window& canvas, int damage, float duration, std::string type, float dt) {
    if (currentSizeA < maxProjectiles) {
            int healthyEnemy = 0;
            int tempHealthy = 0;
            int index = -1;
            float tempx = 0;
            float tempy = 0;
            int canvasx = canvas.getWidth();
            int canvasy = canvas.getHeight();
            for (int i = 0; i < currentSizeE; i++) {
                tempHealthy = earray[i]->getHealth();
                tempx = earray[i]->getX();
                tempy = earray[i]->getY();

                if (tempHealthy > healthyEnemy && tempx > 0 && tempx < canvasx && tempy > 0 && tempy < canvasy) {
                    healthyEnemy = tempHealthy;
                    index = i;
                }
            }
            if (index != -1) {
                int _x = earray[index]->getX()-128;//64 is aoe image/2, centre the image on the enemy
                int _y = earray[index]->getY()-128;
                aoearray[currentSizeA++] = new attack(_x, _y, _x, _y, type, damage, duration);
                //std::cout << "aoe spawned at " << _x << '\t' << _y << std::endl;
            }
        }
}

    //calls enemy update and deletion
void spawnManager::update(GamesEngineeringBase::Window& canvas, hero& player, float dt, float xmove, float ymove) {
    timeElapsed += dt;
    float px = player.getX();
    float py = player.getY();
    attackElapsed += dt;
    for (int i = 0; i < currentSizeE; i++) {
        checkEnemyRange(canvas, i);
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
            checkDeleteEnemyProjectile(player, i);
        }
    }
    for (int i = 0; i < currentSizeA; i++) {
        if (aarray[i]) {
            aarray[i]->update(canvas, xmove, ymove, dt);
            checkDeletePlayerProjectile(player,  i);
        }
    }
    for (int i = 0; i < currentSizeA; i++) {
        if (aoearray[i]) {
            aoearray[i]->update(canvas, xmove, ymove, dt);
            checkAOECollision(player, i, dt);
            if (aoearray[i]->hasDurationEnded()) {
                deleteAOEProjectile(i);
            }
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
        if (aarray[i]) 
            aarray[i]->draw(canvas);
    for (unsigned int i = 0; i < currentSizeEP; i++)
        if (eparray[i]) 
            eparray[i]->draw(canvas);
    for (unsigned int i = 0; i < currentSizeA; i++)
        if (aoearray[i])
            aoearray[i]->draw(canvas);
}

