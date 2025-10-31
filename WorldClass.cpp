#include <iostream>
#include "WorldClass.h"

    world::world() : ts("tile"), LEFT(-1), ABOVE(-1), baseWeights{0.8f, 0.3f, 0.8f, 0.1f} {
        for (unsigned int i = 0; i < worldSizeX; i++)
            for(unsigned int j = 0; j < worldSizeY; j++)
                tarray[i][j] = pickTileFromWeight(i, j);
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
        if (indexi + LEFT >= 0) {
            if (tarray[indexi + LEFT][indexj] == 0)
                weights[0] += 0.4f;
            if (tarray[indexi + LEFT][indexj] == 1)
                weights[1] += 0.8f;
            if (tarray[indexi + LEFT][indexj] == 2)
                weights[2] += 0.4f;
            if (tarray[indexi + LEFT][indexj] == 3)
                weights[3] += 0.8f;
        }
        if (indexi + ABOVE >= 0) {
            if (tarray[indexi][indexj + ABOVE] == 0)
                weights[0] += 0.4f;
            if (tarray[indexi][indexj + ABOVE] == 1)
                weights[1] += 0.8f;
            if (tarray[indexi][indexj + ABOVE] == 2)
                weights[2] += 0.4f;
            if (tarray[indexi][indexj + ABOVE] == 3)
                weights[3] += 0.8f;
        }
        return getWeightedTile(weights);
    }
    void world::draw(GamesEngineeringBase::Window& canvas, int _x, int _y) {
        for (int i = 0; i < worldSizeX; i++)
            for (int j = 0; j < worldSizeY; j++) {
               
                int y = (i * 32) + _x;// no idea why these have to be inverted to work - x controls y and visa versa
                int x = (j * 32) + _y;
                
                ts[tarray[i][j]].draw(canvas, x, y);
            }


    }
    /*void world::print() {
        for (int i = 0; i < worldSizeY; i++) {
            for (int j = 0; j < worldSizeY; j++) {
                if (j == worldSizeY - 1)
                    std::cout << '\n';
                std::cout << tarray[i][j] << '\t';
            }
        }
    }*/
