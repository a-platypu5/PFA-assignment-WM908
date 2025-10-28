#include <iostream>
#include "GamesEngineeringBase.h"

using namespace std;

//draws the spawn restriction area
void drawSquare(GamesEngineeringBase::Window& canvas, int cx, int cy) {
    int half = 250; // half the side length

    for (int x = cx - half; x <= cx + half; x++) {
        for (int y = cy - half; y <= cy + half; y++) {
            // draw only the border
            if (x == cx - half || x == cx + half || y == cy - half || y == cy + half) {
                canvas.draw(x, y, 255, 255, 255);
            }
        }
    }
}

//circle drawing function for showing collision area
void drawCircle(GamesEngineeringBase::Window& canvas, int cx, int cy, int radius) {
    int r2 = radius * radius;
    for (int x = -radius; x < radius + 1; x++) {
        int y = sqrtf(r2 - (x * x));
        if (cx + x > 0 && cx + x < canvas.getWidth()) {
            if (cy + y > 0 && cy + y < canvas.getHeight()) //draw if on screen - otherwise would crash
                canvas.draw(cx + x, cy + y, 255, 0, 0);
            if (cy - y > 0 && cy - y < canvas.getHeight())
                canvas.draw(cx + x, cy - y, 255, 0, 0);
        }
    }
}

class entity {
protected:
    int x;
    int y;
    GamesEngineeringBase::Image image;
public:
    entity(int _x, int _y, string filename) {
        image.load(filename);
        x = _x - image.width / 2; // changes x and y to center of sprite
        y = _y - image.height / 2;
    }

    float getX() { return x; }
    float getY() { return y; }

   

    //draws sprites & collision circle
    void draw(GamesEngineeringBase::Window& canvas) {
        for (int k = 0; k < image.height; k++) 
            if (k + y > 0 && k + y < canvas.getHeight()) 
                for (int j = 0; j < image.width; j++) 
                    if (j + x > 0 && j + x < canvas.getWidth()) 
                        if (image.alphaAtUnchecked(j, k) > 0) 
                            canvas.draw(x + j, y + k, image.atUnchecked(j, k));
                        
        drawCircle(canvas, x + image.width / 2, y + image.height / 2, image.width / 3);
    }


    bool collision(entity& e) {
        int dx = x - e.x;
        int dy = y - e.y;

        // this should be set in constructor
        float radius = static_cast<float>(image.width / 3);
        //  float d = sqrtf(dx * dx + dy * dy); // can do without sqrtf also
        //  return d < 2.f * radius; 
        float d = dx * dx + dy * dy;
        return d < 4.f * radius * radius;
    }
};

class hero : public entity {
public:
    hero(int _x, int _y, string filename) : entity(_x, _y, filename) {
    }


    void update(GamesEngineeringBase::Window& canvas, int _x, float _y) {
        x = _x - image.width / 2;
        y = _y - image.height / 2;
    }
};

class enemy : public entity {
    int speed = 3;
public:
    enemy(int _x, int _y, string filename) : entity(_x, _y, filename) {
    }

    //moves the enemy toward the player, but takes into account virtual player movement
    void update(hero& player, int xmove, int ymove) {
        int px = player.getX();
        int py = player.getY();
        if (x > px + 20)//+- 20 avoids enemies flicxkering at higher speeds, and adds an area enemies target
            x -= speed;
        else if (x < px - 20)
            x += speed;
        if (y > py + 20)
            y -= speed;
        else if (y < py - 20)
            y += speed;
        if (xmove != 0)
            x += xmove; // changes movement of enemies when player moves away
        if (ymove != 0)
            y += ymove;
    }
};


class pattack : public entity {
    int n = 0;
    int frameTimer = 0;
public:
    pattack(int _x, int _y, string filename) : entity(_x, _y, filename) {
    }

    void update(hero& player, int xmove, int ymove) {
        //target and move towards closest enemy
        //keep target even if new target aquired.
        frameTimer++;
        if (frameTimer >= 5) {
            frameTimer = 0;
            n++;
            if (n >= 8)
                n = 0;
        }
       
        image.load("Resources/shuriken" + std::to_string(n) + ".png"); //scrolls through 8 .png
        if (xmove != 0)
            x += xmove; // changes movement of enemies when player moves away
        if (ymove != 0)
            y += ymove;
    }
};


const unsigned int maxEnemies = 1000;
const unsigned int maxProjectiles = 100;

class spawnManager {
    enemy* earray[maxEnemies];
    pattack* aarray[maxProjectiles];
    float timeElapsed = 0;
    float spawnThreshold = 3.f;
    int currentSizeE = 0;
    float attackElapsed = 0;
    float attackDelay = 3.f;
    int currentSizeA = 0;

    //spawns enemies on the map, outside an area around the player
    void spawnEnemy(GamesEngineeringBase::Window& canvas, hero& player) {
        if (currentSizeE < maxEnemies) {
            if (timeElapsed > spawnThreshold) {
                int rx = rand() % canvas.getWidth();//mapx max
                int ry = rand() % canvas.getHeight();//mapy max
                int x;
                int y;
                int safeRange = 250;

                //need to use a get funciton as the x, y is protected/private

                int px = player.getX() + 83 / 2;//+ image. width
                int py = player.getY() + 115 / 2; //+ image.height

                //cout << rx << '\t' << ry << endl;
                if (abs(rx - px) > safeRange || abs(ry - py) > safeRange) {
                    x = rx;
                    y = ry;
                }
                //randomly move enemy to an edge of the safe spawn area if initially inside
                else {
                    bool coin = rand() % 2;
                    if (coin) {
                        x = (rand() % 2 == 0 ? px + safeRange : px - safeRange);
                        y = ry;
                    }
                    else {
                        x = rx;
                        y = (rand() % 2 == 0 ? py + safeRange : py - safeRange);
                    }
                }

                //cout << x << '\t' << y<< endl;
                //spawns enemy in heap array on an decreasing time interval to a min of 0.5f
                earray[currentSizeE++] = new enemy(x, y, "Resources/L2.png");
                timeElapsed = 0.f;
                spawnThreshold -= 0.2f;
                spawnThreshold = max(spawnThreshold, 0.5f);
            }
        }
    }

    //makes sure enemy exists before removing if player crashed
    void checkDeleteEnemy(GamesEngineeringBase::Window& canvas, hero& player, int i) {
        if (earray[i]->collision(player)) {
            delete earray[i];
            earray[i] = nullptr;
            cout << "player damaged" << endl;
        }
    }

    void spawnProjectile(GamesEngineeringBase::Window& canvas, hero& player) {
        if (currentSizeA < maxProjectiles)
            if (attackElapsed > attackDelay) {
                int x = player.getX();
                int y = player.getY();
                aarray[currentSizeA++] = new pattack(x, y, "Resources/shuriken0.png");
                attackElapsed = 0;
            }
    }

    void checkDeleteProjectile() {
        //if collision with any enemy - delete enemy and prohjectile
    }

public:
    spawnManager() {}

    ~spawnManager() {
        for (unsigned int i = 0; i < currentSizeE; i++) {
            if (earray[i])
                delete earray[i];
        }
    }

    //calls enemy update and deletion
    void update(GamesEngineeringBase::Window& canvas, hero& player, float dt, int xmove, int ymove) {
        timeElapsed += dt;
        attackElapsed += dt;
        spawnProjectile(canvas, player);
        spawnEnemy(canvas, player);
        for (int i = 0; i < currentSizeE; i++) {
            if (earray[i]) {
                earray[i]->update(player, xmove, ymove);
                checkDeleteEnemy(canvas, player, i);
            }
        }
        for (int i = 0; i < currentSizeA; i++) {
            if (aarray[i]) {
                aarray[i]->update(player, xmove, ymove);
            }
        }
    }

    void draw(GamesEngineeringBase::Window& canvas) {
        for (unsigned int i = 0; i < currentSizeE; i++)
            if (earray[i])
                earray[i]->draw(canvas);
        for (unsigned int i = 0; i < currentSizeA; i++)
            if (aarray[i]) {
                aarray[i]->draw(canvas);
            }
    }

    bool collision(hero& player) {
        for (int i = 0; i < currentSizeE; i++) {
            if (earray[i] != nullptr) {
                if (earray[i]->collision(player)) {
                    cout << "Player collided" << endl;
                    return true;
                }
            }
        }
        return false;
    }
};

class GameManager {
    spawnManager sm;
    hero player;
    GamesEngineeringBase::Window& canvas;
    GamesEngineeringBase::Timer tim;
    //sets center map x,y
    int cx;
    int cy;
    //controls slight player movement to feel more immersive
    float tx = cx;//target of player is centre by default
    float ty = cy;
    float xpos = cx;//xpos is the current xpos to draw the player
    float ypos = cy;
    float smooth = 0.01f;
    int move = 25;//speed of percieved player movement
    int mapx = 0;
    int mapy = 0;
    int speed = 5;
public:
    GameManager(GamesEngineeringBase::Window& win)
        : canvas(win),
        cx(win.getWidth() / 2),
        cy(win.getHeight() / 2),
        player(cx, cy, "Resources/L.png") {}
    void update() {
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

    void draw() {
        for (unsigned int y = 0; y < 2000; y++)
            for (unsigned int x = 0; x < 2000; x++)
                if (x + mapx > 0 && x + mapx < canvas.getWidth()) 
                    if (y + mapy > 0 && y + mapy < canvas.getHeight()) 
                        if (x % 50 == 0 && y % 50 == 0) 
                            canvas.draw(x + mapx, y + mapy, 255, 255, 255);
                       
        drawSquare(canvas, cx, cy);
        sm.draw(canvas);
        player.draw(canvas);
    }
};




int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(1024, 768, "2dGame");
   
    GameManager gm(canvas);
    // Main game loop
    while (true)
    {
        // Check for input (key presses or window events)
        canvas.checkInput();

        // Clear the window for the next frame rendering
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        gm.update();
        gm.draw();
        //current temp map object
        
        // Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}