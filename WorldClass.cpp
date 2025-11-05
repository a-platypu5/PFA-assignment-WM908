#include <iostream>
#include "WorldClass.h"

    world::world() : ts("tile"), LEFT(-1), ABOVE(-1), baseWeights{0.8f, 0.3f, 0.8f, 0.1f, 0.f}, mapType(0) {
        tileMap = new unsigned int* [worldSizeX];
        for (int i = 0; i < worldSizeX; i++)
            tileMap[i] = new unsigned int[worldSizeY];

        std::cout << "Please select which map type you want to use." << std::endl;
        std::cout << "Map type 1: Fixed Border" << '\t' << "Map type 2: Infinite scroller" << std::endl;
        while (mapType != 1 && mapType != 2) {
            std::cout << "Type '1' for fixed, or '2' for infinite:" << std::endl;
            std::cin >> mapType;
        }
        switch (mapType) {
        case 1: std::cout << "You have selected a fixed border map type" << std::endl << std::endl; break;
        case 2: std::cout << "You have selected an infinite scroller map type" << std::endl << std::endl; break;
        }

        for (unsigned int i = 0; i < worldSizeX; i++)
            for (unsigned int j = 0; j < worldSizeY; j++) {
                if (mapType == 1 && (i == 0 || j == 0 || i == (worldSizeX - 1) || j == (worldSizeY - 1)))
                        tileMap[j][i] = 4;
                else if (mapType == 1 || mapType == 2)
                    tileMap[j][i] = pickTileFromWeight(i, j);
            }
    }

    world::~world() {
        delete[] tileMap;
    }
    int world::getWeightedTile(const float weights[tileNum]) {
        float total = 0.0f;
        for (int i = 0; i < tileNum; i++)
            total += weights[i];

        float r = static_cast<float>(rand()) / RAND_MAX * total;

        for (int i = 0; i < tileNum; i++) {
            r -= weights[i];
            if (r <= 0.0f)
                return i;
        }
        return 0;
    }
    int world::pickTileFromWeight(int indexi, int indexj) {
        float weights[tileNum];
        for (int i = 0; i < tileNum; i++)
            weights[i] = baseWeights[i];
        if (indexj == 0)
            return getWeightedTile(weights);

        switch (tileMap[indexj + LEFT][indexi]) {
        case 0: weights[0] += 2.f; break;
        case 1: weights[1] += 0.8f; break;
        case 2: weights[2] += 0.4f; break;
        case 3: weights[3] += 0.8f; break;
        }
        if(indexi == 0)
            return getWeightedTile(weights);
        switch (tileMap[indexj][indexi + ABOVE]) {
        case 0: weights[0] += 4.f; break;
        case 1: weights[1] += 0.8f; break;
        case 2: weights[2] += 0.4f; break;
        case 3: weights[3] += 0.8f; break;
        }
        switch (tileMap[indexj][indexi + ABOVE] && tileMap[indexj + LEFT][indexi]) {
        case 0: weights[0] += 0.2f; break;
        case 1: weights[1] -= 1.4f; break;
        case 2: weights[2] += 0.2f; break;
        case 3: weights[3] -= 1.4f; break;
        }
        return getWeightedTile(weights);
    }
    void world::draw(GamesEngineeringBase::Window& canvas, float _x, float _y) {
        for (int i = 0; i < worldSizeX; i++)
            for (int j = 0; j < worldSizeY; j++) {
                float x = (i * 32) + _x - (worldSizeX*32)/2;
                float y = (j * 32) + _y - (worldSizeY*32)/2; 
                ts[tileMap[j][i]].draw(canvas, x, y);
            }
    }
    
    //shifts all the existing tiles up or down the array and inputs new tiles into the new emtpy array layer
    void world::update(float& mapx, float& mapy) {
        if (mapType == 2) {//may put another check in the gameManager update so this doesnt even get called
            if (mapx >= 32) {
                mapx = 0;
                for (int j = 0; j < worldSizeY; j++) {
                    for (int i = worldSizeX - 1; i > 0; i--)
                        tileMap[j][i] = tileMap[j][i - 1];
                    tileMap[j][0] = pickTileFromWeight(0, j);
                }
            }
            if (mapx <= -32) {
                mapx = 0;
                for (int j = 0; j < worldSizeY; j++) {
                    for (int i = 0; i < worldSizeX; i++)
                        tileMap[j][i] = tileMap[j][i + 1];
                    tileMap[j][worldSizeX - 1] = pickTileFromWeight(worldSizeX - 1, j);
                }
            }
            if (mapy >= 32) {
                mapy = 0;
                for (int i = 0; i < worldSizeX; i++) {
                    for (int j = worldSizeY - 1; j > 0; j--)
                        tileMap[j][i] = tileMap[j - 1][i];
                    tileMap[0][i] = pickTileFromWeight(i, 0);
                }
            }
            if (mapy <= -32) {
                mapy = 0;
                for (int i = 0; i < worldSizeX; i++) {
                    for (int j = 0; j < worldSizeY - 1; j++)
                        tileMap[j][i] = tileMap[j + 1][i];
                    tileMap[worldSizeY - 1][i] = pickTileFromWeight(i, worldSizeY - 1);
                }
            }
        }
    }

    void world::print() {
        for (int i = 0; i < worldSizeY; i++) {
            for (int j = 0; j < worldSizeY; j++) {
                if (j == worldSizeY - 1)
                    std::cout << '\n';
                std::cout << tileMap[i][j] << '\t';
            }
        }
    }
