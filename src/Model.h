#ifndef MODEL_H
#define MODEL_H

#include "FlyingObject.h"
#include "Asteroid.h"
#include "Missile.h"
#include "Spaceship.h"
#include <memory>
#include <vector>

class Model {
private:
    int screenWidth;
    int screenHeight;

    std::shared_ptr<Spaceship> spaceship;
    std::vector<std::shared_ptr<Asteroid>> asteroids;
    std::shared_ptr<Missile> missile;

    bool missileActive;
    int score;

    int getRandomInt(int min, int max) const;
    double getRandomDouble(double min, double max) const;
    void spawnAsteroid();

public:
    Model(int screenWidth, int screenHeight);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void shoot();

    int update();
    std::vector<std::shared_ptr<FlyingObject>> getFlyingObjects() const;
    int getScore() const;
};

#endif // MODEL_H
