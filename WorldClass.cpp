#include <iostream>
#include "WorldClass.h"

    world::world() : ts("tile"), LEFT(-1), ABOVE(-1), baseWeights{0.8f, 0.3f, 0.8f, 0.1f, 0.f} {
        tileMap = new unsigned int* [worldSizeX];
        for (int i = 0; i < worldSizeX; i++)
            tileMap[i] = new unsigned int[worldSizeY];

        for (unsigned int i = 0; i < worldSizeX; i++)
            for (unsigned int j = 0; j < worldSizeY; j++) {
                if (i == 0 || j == 0 || i == (worldSizeX - 1) || j == (worldSizeY - 1))
                    tileMap[i][j] = 4;
                else
                    tileMap[i][j] = pickTileFromWeight(i, j);
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

            switch (tileMap[indexi + LEFT][indexj]) {
            case 0: weights[0] += 2.f; break;
            case 1: weights[1] += 0.8f; break;
            case 2: weights[2] += 0.4f; break;
            case 3: weights[3] += 0.8f; break;
            }
            switch (tileMap[indexi][indexj + ABOVE]) {
            case 0: weights[0] += 4.f; break;
            case 1: weights[1] += 0.8f; break;
            case 2: weights[2] += 0.4f; break;
            case 3: weights[3] += 0.8f; break;
            }
            switch (tileMap[indexi][indexj + ABOVE] && tileMap[indexi + LEFT][indexj]) {
            case 0: weights[0] += 0.2f; break;
            case 1: weights[1] -= 1.4f; break;
            case 2: weights[2] += 0.2f; break;
            case 3: weights[3] -= 1.4f; break;
            }
        return getWeightedTile(weights);
    }
    void world::draw(GamesEngineeringBase::Window& canvas, int _x, int _y) {
        for (int i = 0; i < worldSizeX; i++)
            for (int j = 0; j < worldSizeY; j++) {
               
                int x = (i * 32) + _y;// no idea why these have to be inverted to work - x controls y and visa versa
                int y = (j * 32) + _x;
                
                ts[tileMap[i][j]].draw(canvas, x, y);
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
