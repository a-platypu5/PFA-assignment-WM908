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
    tx(cx), ty(cy), xpos(cx), ypos(cy), smooth(0.01f), move(25), mapx(0), mapy(0), speed(4), gameMode(0), totalTime(0),
    fps(0.0f), frameCounter(0), fpsTimer(0.0f){

    std::cout << "Please select which GameMode you want to play." << std::endl;
    std::cout << "GameMode 1: 2 Minute Timer" << '\t' << "GameMode 2: Endless Mode" << std::endl;
    while (gameMode != 1 && gameMode != 2) {
        std::cout << "Type '1' for fixed, or '2' for infinite:" << std::endl;
        std::cin >> gameMode;
    }
    switch (gameMode) {
    case 1: std::cout << "You have selected a 2 minute Timer" << std::endl << std::endl; break;
    case 2: std::cout << "You have selected an endless mode" << std::endl << std::endl; break;
    }
}

float GameManager::averagefps(float dt) {
    fpsTimer += dt;
    frameCounter++;
    if (fpsTimer >= 1.0f) {
        fps = frameCounter / fpsTimer;
        frameCounter = 0;
        fpsTimer = 0;
        return fps;
    }
    else
        return 0;
}

bool GameManager::update() {
    float dt = tim.dt();
    totalTime += dt;
    float fpsTEMP = averagefps(dt);
    if (fpsTEMP != 0)
        std::cout << fpsTEMP << std::endl;

    if (gameMode == 2 || (gameMode == 1 && totalTime < 120)) {

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
        return true;
    }
    else {
        if (gameMode == 1 && totalTime >= 120) {
            std::cout << "Congradulations, you made it to the 2 minute mark" << std::endl;
        }
        else if ((gameMode == 1 && totalTime < 120) || (gameMode == 2)) {
            std::cout << "GAME OVER" << std::endl << std::endl;
            std::cout << "You survived " << static_cast<int>(totalTime) / 60 << " minutes and " << static_cast<int>(totalTime) % 60 << std::endl;
        }
        return false;
    }
}

void GameManager::draw() {
    w.draw(canvas, mapx, mapy);

    //drawSquare(canvas, cx, cy);
    sm.draw(canvas);
    player.draw(canvas);
}
