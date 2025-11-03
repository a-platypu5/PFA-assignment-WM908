#include <iostream>
#include "GameManager.h"


//draws the spawn restriction area
void drawSquare(GamesEngineeringBase::Window& canvas, int cx, int cy) {
    int half = 250; // half the side length
    for (int x = cx - half; x <= cx + half; x++)
        for (int y = cy - half; y <= cy + half; y++)
            // draw only the border
            if (x == cx - half || x == cx + half || y == cy - half || y == cy + half)
                canvas.draw(x, y, 255, 255, 255);
}


GameManager::GameManager(GamesEngineeringBase::Window& win)
    : canvas(win), cx(win.getWidth() / 2), cy(win.getHeight() / 2), player(cx, cy, "Resources/Hero.png"),
    tx(cx), ty(cy), xpos(cx), ypos(cy), smooth(0.01f), move(25), mapx(0), mapy(0), speed(4) {
}
void GameManager::update() {
    float dt = tim.dt();

    //target for player to move toward - for aesthetic movement
    tx = cx;
    ty = cy;
    //detection of movement of player to globally move enemies around, creating the illusion of the player moviong around enemies
    int xmove = 0;
    int ymove = 0;

    if (canvas.keyPressed('W')) {
        ty -= move;
        ymove += speed;
        mapy += speed;
    }
    if (canvas.keyPressed('S')) {
        ty += move;
        ymove -= speed;
        mapy -= speed;
    }
    if (canvas.keyPressed('A')) {
        tx -= move;
        xmove += speed;
        mapx += speed;
    }
    if (canvas.keyPressed('D')) {
        tx += move;
        xmove -= speed;
        mapx -= speed;
    }
    //player smoothing movement
    xpos += (tx - xpos) * smooth;
    ypos += (ty - ypos) * smooth;

    player.update(canvas, xpos, ypos); 
    sm.update(canvas, player, dt, xmove, ymove);
    w.update(mapx, mapy);
}

void GameManager::draw() {
    w.draw(canvas, mapx, mapy);

    //drawSquare(canvas, cx, cy);
    sm.draw(canvas);
    player.draw(canvas);
}
