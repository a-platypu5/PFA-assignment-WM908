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
    int cx;
    int cy;
    //controls slight player movement to feel more immersive
    float tx;//target of player is centre by default
    float ty;
    float xpos;//xpos is the current xpos to draw the player
    float ypos;
    float smooth;
    int move;//speed of percieved player movement
    int mapx;
    int mapy;
    int speed;
public:
    GameManager(GamesEngineeringBase::Window& win);
    void update();

    void draw();
};

#endif
