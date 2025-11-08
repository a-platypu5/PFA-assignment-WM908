#include <iostream>
#include "EntityClass.h"

void drawCircle(GamesEngineeringBase::Window& canvas, float cx, float cy, int radius) {
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

entity::entity(float _x, float _y, std::string filename) {
    image.load(filename);
    x = _x + (image.width / 2); // changes x and y to center of sprite
    y = _y + (image.height / 2);

    radius = static_cast<float>(image.width / 3);
}

float entity::getX() { return x; }
float entity::getY() { return y; }

void entity::drawCentre(GamesEngineeringBase::Window& canvas) {
    for (int m = -2; m < 2; m++)
        if (m + x > 0 && m + x < canvas.getWidth())
            for (int n = -2; n < 2; n++)
                if (n + y > 0 && n + y < canvas.getHeight())
            canvas.draw(x + m, y + n, 0, 255, 0);
}

 //draws sprites & collision circle
 void entity::draw(GamesEngineeringBase::Window& canvas) { //lots of +- image.h/w /2 to centralise image location
     for (int k = 0; k < image.height; k++)
         if (k + y > (0 + (image.height/2)) && k + y < (canvas.getHeight() + image.height/2))
             for (int j = 0; j < image.width; j++)
                 if (j + x > (0 + (image.width/2)) && j + x < (canvas.getWidth() + image.width/2))
                     if (image.alphaAtUnchecked(j, k) > 0)
                         canvas.draw(x + j - image.width/2, y + k - image.height/2, image.atUnchecked(j, k));

     //drawCircle(canvas, x, y, image.width / 3);
     //drawCentre(canvas);
 }

 bool entity::collision(entity& e) {
     if (&e != NULL) { // null checking the entity to make sure the maths can complete
         int dx = x - e.x;
         int dy = y - e.y;

         int d = dx * dx + dy * dy;
         float r2 = radius + e.radius;

         return d < r2 * r2;
     }
     else return false;
 }
