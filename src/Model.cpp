#include "Model.h"
#include "FlyingObject.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Model::Model(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), missileActive(false), score(0)
{
    srand(static_cast<unsigned>(time(nullptr)));

    spaceship = std::make_shared<Spaceship>(screenWidth / 2.0, screenHeight / 2.0, 50.0, 0.0);
    missile = nullptr;

    for (int i = 0; i < 3; i++) spawnAsteroid();
}

int Model::getRandomInt(int min, int max) const {
    return min + rand() % (max - min + 1);
}

double Model::getRandomDouble(double min, double max) const {
    return min + (max - min) * (static_cast<double>(rand()) / RAND_MAX);
}

void Model::spawnAsteroid() {
    int index = getRandomInt(0, 7);
    if (index >= 4) index++; // saute la case centrale (cellule (1,1))
    int row = index / 3;
    int col = index % 3;

    double cellW = screenWidth / 3.0;
    double cellH = screenHeight / 3.0;

    double x = getRandomDouble(col * cellW + 20.0, (col + 1) * cellW - 20.0);
    double y = getRandomDouble(row * cellH + 20.0, (row + 1) * cellH - 20.0);

    double angle = getRandomDouble(-180.0, 180.0);
    double speed = 1.5;
    double radians = M_PI * (180.0 - angle) / 180.0;
    double vx = speed * sin(radians);
    double vy = -speed * cos(radians);

    asteroids.push_back(std::make_shared<Asteroid>(x, y, 80.0, vx, vy, 2));
}

void Model::moveUp() {
    spaceship->speedUp(0.4);
}

void Model::moveDown() {
    spaceship->speedDown(0.4);
}

void Model::moveLeft() {
    spaceship->rotate(-3.0);
}

void Model::moveRight() {
    spaceship->rotate(3.0);
}

void Model::shoot() {
    if (!missileActive) {
        double radians = spaceship->getAngle() * M_PI / 180.0;
        double frontX = spaceship->getX() + 25.0 * sin(radians);
        double frontY = spaceship->getY() - 25.0 * cos(radians);
        missile = std::make_shared<Missile>(frontX, frontY, 12.0, 15.0, spaceship->getAngle());
        missileActive = true;
    }
}

int Model::update() {
    spaceship->move(screenWidth, screenHeight);

    for (auto& ast : asteroids)
        ast->move(screenWidth, screenHeight);

    if (missileActive && missile) {
        missileActive = !missile->move(screenWidth, screenHeight);
        if (!missileActive)
            missile.reset();
    }

    if (!spaceship->GetInvincible()) {
        for (auto& ast : asteroids) {
            if (FlyingObject::collide(*spaceship, *ast)) {
                spaceship->setShieldLevel(spaceship->getShieldLevel() - 0.25);
                spaceship->SetInvincibleFor(1.5);
                if (spaceship->getShieldLevel() <= 0.0)
                    return -1;
                break;
            }
        }
    }

    if (missileActive && missile) {
        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (FlyingObject::collide(*missile, *asteroids[i])) {
                double missileVx = missile->getXSpeed();
                double missileVy = missile->getYSpeed();

                missileActive = false;
                missile.reset();

                auto child = asteroids[i]->Explode(missileVx, missileVy);
                if (child) {
                    asteroids.push_back(child);
                } else {
                    score += 100;
                    asteroids.erase(asteroids.begin() + i);
                }
                break;
            }
        }
    }

    if (asteroids.empty())
        return 1;

    return 0;
}

std::vector<std::shared_ptr<FlyingObject>> Model::getFlyingObjects() const {
    std::vector<std::shared_ptr<FlyingObject>> objects(asteroids.begin(), asteroids.end());
    objects.push_back(spaceship);
    if (missileActive && missile)
        objects.push_back(missile);
    return objects;
}

int Model::getScore() const {
    return score;
}
