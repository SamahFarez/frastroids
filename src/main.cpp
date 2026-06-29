#include "Controller.h"

int gameLoop()
{
    Controller controller(800, 600, 60, 50, 10);
    controller.LaunchGame();
    return 0;
}

#ifndef ASTEROID_TESTS
int main()
{
    gameLoop();
    return 0;
}
#endif