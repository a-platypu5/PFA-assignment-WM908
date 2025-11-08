#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "GamesEngineeringBase.h"
#include "SpawnManager.h"
#include "WorldClass.h"

//draws the spawn restriction area
void drawSquare(GamesEngineeringBase::Window& canvas, int cx, int cy);

class GameManager {
    spawnManager sm;
    hero player;
    world w;
    GamesEngineeringBase::Window& canvas;
    GamesEngineeringBase::Timer tim;

    //sets center map x,y
    int cx, cy;
    //controls slight player movement to feel more immersive
    float tx, ty;//target of player is centre by default
    float xpos, ypos;//xpos is the current xpos to draw the player
    float smooth;
    int move;//speed of percieved player movement
    float mapx, mapy;
    int speed;
    int gameMode;
    float totalTime;
    float fps;
    int frameCounter;
    float fpsTimer;
    bool isMapFixed;
    float minMapx, maxMapx;
    float minMapy, maxMapy;
public:
    GameManager(GamesEngineeringBase::Window& win);
    float averagefps(float dt);
    bool update();

    void draw();
};

#endif
