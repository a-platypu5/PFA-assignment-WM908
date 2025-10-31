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
    : canvas(win), cx(win.getWidth() / 2), cy(win.getHeight() / 2), player(cx, cy, "Resources/L.png"),
    tx(cx), ty(cy), xpos(cx), ypos(cy), smooth(0.01f), move(25), mapx(0), mapy(0), speed(5) {
}
void GameManager::update() {
    float dt = tim.dt();

    //target for player to move toward
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
    sm.collision(player);
}

void GameManager::draw() {
    for (unsigned int y = 0; y < 2000; y++)
        for (unsigned int x = 0; x < 2000; x++)
            if (x + mapx > 0 && x + mapx < canvas.getWidth())
                if (y + mapy > 0 && y + mapy < canvas.getHeight())
                    if (x % 50 == 0 && y % 50 == 0)
                        canvas.draw(x + mapx, y + mapy, 255, 255, 255);

    w.draw(canvas, mapx, mapy);

    drawSquare(canvas, cx, cy);
    sm.draw(canvas);
    player.draw(canvas);
}
