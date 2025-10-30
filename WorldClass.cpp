#include <iostream>
#include "WorldClass.h"
#include "TileSetClass.h"


    world::world() : ts("tile"), LEFT(-1), ABOVE(-32), baseWeights{0.8f, 0.3f, 0.1f} {// - 32 is number in row
        for (unsigned int i = 0; i < worldSize; i++)
            tarray[i] = pickTileFromWeight(i);
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
    int world::pickTileFromWeight(int index) {
        float weights[tileNum];
        for (int i = 0; i < tileNum; i++)
            weights[i] = baseWeights[i];
        if (index + ABOVE >= 0) {
            if (tarray[index + ABOVE] == 0)
                weights[0] += 0.8f;
            if (tarray[index + ABOVE] == 1)
                weights[1] += 0.8f;
            if (tarray[index + ABOVE] == 2)
                weights[2] += 0.8f;
        }
        if (index + LEFT >= 0) {
            if (tarray[index + LEFT] == 0)
                weights[0] += 0.8f;
            if (tarray[index + LEFT] == 1)
                weights[1] += 0.8f;
            if (tarray[index + LEFT] == 2)
                weights[2] += 0.8f;
        }
        return getWeightedTile(weights);
    }
    void world::draw(GamesEngineeringBase::Window& canvas, int _x, int _y) {
        for (int i = 0; i < 32; i++)
            for (int j = 0; j < 32; j++) {
                int index = i * 32 + j;
                int y = (i * 32) + _x;// no idea why these have to be inverted to work - x controls y and visa versa
                int x = (j * 32) + _y;
                ts[tarray[index]].draw(canvas, x, y);
            }


    }
    /*void world::print() {
        for (int i = 0; i < worldSize; i++) {
            if (worldSize % (i + 1) == 0)
                std::cout << '\n';
            std::cout << tarray[i] << '\t';
        }
    }*/
