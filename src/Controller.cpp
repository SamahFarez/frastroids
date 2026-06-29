#include "Controller.h"
#include <SDL3/SDL.h>

Controller::Controller(int width, int height, int fps, int shipSize, int missileSize)
    : framework(std::make_unique<Framework>(width, height, fps, shipSize, missileSize)),
      model(std::make_unique<Model>(width, height)),
      view(std::make_unique<View>(framework.get()))
{
}

void Controller::LaunchGame() {
    bool running = true;
    int finalState = 0;

    while (running) {
        int input = Framework::getInput();

        if (input == SDL_EVENT_QUIT || input == SDLK_ESCAPE) {
            running = false;
        } else if (input == SDLK_UP) {
            model->moveUp();
        } else if (input == SDLK_DOWN) {
            model->moveDown();
        } else if (input == SDLK_LEFT) {
            model->moveLeft();
        } else if (input == SDLK_RIGHT) {
            model->moveRight();
        } else if (input == SDLK_SPACE) {
            model->shoot();
        }

        int gameState = model->update();

        if (gameState != 0) {
            finalState = gameState;
            running = false;
        }

        view->refresh(model->getFlyingObjects(), model->getScore());

        if (finalState != 0) {
            view->showEndScreen(finalState == 1);
        }

        framework->update();
    }

    if (finalState != 0) {
        Uint32 start = SDL_GetTicks();
        while (SDL_GetTicks() - start < 3000) {
            SDL_Event e;
            SDL_PollEvent(&e);
            SDL_Delay(16);
        }
    }
}
