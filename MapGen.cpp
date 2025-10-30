#include <iostream>
#include "GamesEngineeringBase.h"

class tile {
    GamesEngineeringBase::Image image;
public:
    tile() {}
    void load(std::string filename) {
        image.load(filename);
    }
    void draw(GamesEngineeringBase::Window& canvas, int y, int x) {
        for (unsigned int i = 0; i < image.height; i++)
            if (y + i > 0 && (y + i) < (canvas.getHeight()))
                for (unsigned int n = 0; n < image.width; n++)
                    if(x + n > 0 && (x + n) < (canvas.getWidth()))
                        canvas.draw(x + n, y + i, image.atUnchecked(n, i));
    }
    unsigned int getHeight() { return image.height; }
    unsigned int getWidth() { return image.width; }
    GamesEngineeringBase::Image& getSprite() { return image; }

};


const unsigned int tileNum = 3;
class tileSet {
    tile t[tileNum];
public:
    // create and load tiles here
    tileSet(std::string pre = "") {
        for (unsigned int i = 0; i < tileNum; i++) {
            std::string filename;
            filename = "Resources/" + pre + std::to_string(i) + ".png";
            t[i].load(filename);
        }
    }
    // access individual tile here
    tile& operator[](unsigned int index) { return t[index]; }
};

const int worldSize = 1024;
class world {
    tileSet ts;
    unsigned int tarray[worldSize];
    int LEFT = -1;
    int ABOVE = -32;
    float baseWeights[tileNum] = {
        0.6f,
        0.3f,
        0.1f
    };
public:
    world() : ts(){
        for (unsigned int i = 0; i < worldSize; i++)
            tarray[i] = pickTileFromWeight(i);
    }
    int getWeightedTile(const float weights[tileNum]) {
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
    int pickTileFromWeight(int index) {
        float weights[tileNum];
        for (int i = 0; i < tileNum; i++)
            weights[i] = baseWeights[i];
        if (index + ABOVE >= 0) {
            if (tarray[index + ABOVE] == 0)
                weights[0] += 0.2f;
            if (tarray[index + ABOVE] == 1)
                weights[1] += 0.2f;
            if (tarray[index + ABOVE] == 2)
                weights[2] += 0.2f;
        }
        if (index + LEFT >= 0) {
            if (tarray[index + LEFT] == 0)
                weights[0] += 0.2f;
            if (tarray[index + LEFT] == 1)
                weights[1] += 0.2f;
            if (tarray[index + LEFT] == 2)
                weights[2] += 0.2f;
        }
        return getWeightedTile(weights);
    }
    void draw(GamesEngineeringBase::Window& canvas) {
        for (int y = 0; y < 32; y++)
            for (int x = 0; x < 32; x++) {
                int index = y * 32 + x;
                x = x * 32;
                y = y * 32;
                ts[tarray[index]].draw(canvas, x, y);
            }
        

    }
    void print() {
        for (int i = 0; i < worldSize; i++) {
            if (worldSize % (i+1) == 0)
                std::cout << '\n';
            std::cout << tarray[i] << '\t';
        }
    }
};