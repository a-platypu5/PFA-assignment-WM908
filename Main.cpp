#include <iostream>
#include "WorldClass.h"
#include "HeroClass.h"
#include "EnemyClass.h"
#include "PlayerAttackClass.h"
#include "SpawnManager.h"
#include "GameManager.h"


int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(1024, 768, "2dGame");
    srand(static_cast<unsigned int>(time(nullptr)));
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