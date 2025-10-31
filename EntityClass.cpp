#include <iostream>
#include "EntityClass.h"

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

entity::entity(int _x, int _y, std::string filename) {
    image.load(filename);
    x = _x - image.width / 2; // changes x and y to center of sprite
    y = _y - image.height / 2;
}

float entity::getX() { return x; }
float entity::getY() { return y; }

 //draws sprites & collision circle
 void entity::draw(GamesEngineeringBase::Window& canvas) {
     for (int k = 0; k < image.height; k++)
         if (k + y > 0 && k + y < canvas.getHeight())
             for (int j = 0; j < image.width; j++)
                 if (j + x > 0 && j + x < canvas.getWidth())
                     if (image.alphaAtUnchecked(j, k) > 0)
                         canvas.draw(x + j, y + k, image.atUnchecked(j, k));

     drawCircle(canvas, x + image.width / 2, y + image.height / 2, image.width / 3);
 }

 bool entity::collision(entity& e) {
     int dx = x - e.x;
     int dy = y - e.y;

     // this should be set in constructor
     float radius = static_cast<float>(image.width / 3);
     //  float d = sqrtf(dx * dx + dy * dy); // can do without sqrtf also
     //  return d < 2.f * radius; 
     float d = dx * dx + dy * dy;
     return d < 4.f * radius * radius;
 }
