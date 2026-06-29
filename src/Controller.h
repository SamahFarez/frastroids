#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Framework.h"
#include "Model.h"
#include "View.h"
#include <memory>

class Controller {
private:
    std::unique_ptr<Framework> framework;
    std::unique_ptr<Model> model;
    std::unique_ptr<View> view;

public:
    Controller(int width, int height, int fps, int shipSize, int missileSize);
    void LaunchGame();
};

#endif // CONTROLLER_H
