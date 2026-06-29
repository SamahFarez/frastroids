#include "Asteroid.h"
#include <memory>
#include <cmath>

Asteroid::Asteroid(double x, double y, double size, double xSpeed, double ySpeed, double nbExplosionsLeft)
    : FlyingObject(x, y, size, xSpeed, ySpeed), nbExplosionsLeft(nbExplosionsLeft)
{
}

double Asteroid::getExplosionsLeft() const {
    return nbExplosionsLeft;
}

std::shared_ptr<Asteroid> Asteroid::Explode(double newXSpeed, double newYSpeed) {
    if (nbExplosionsLeft <= 0.0) {
        return nullptr;
    }

    double newSize = size * 0.6;
    if (newSize < 10.0) newSize = 10.0;

    nbExplosionsLeft -= 1.0;
    size = newSize;

    // Utilise la direction du missile mais limite la vitesse à une plage normale
    double speed = sqrt(newXSpeed * newXSpeed + newYSpeed * newYSpeed);
    if (speed > 1.8) {
        newXSpeed = newXSpeed / speed * 1.8;
        newYSpeed = newYSpeed / speed * 1.8;
    }

    return std::make_shared<Asteroid>(x, y, newSize, newXSpeed, newYSpeed, nbExplosionsLeft);
}

std::string Asteroid::GetTypeName() const {
    return "Asteroid";
}
