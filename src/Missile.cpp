#include "Missile.h"
#include <cmath>

Missile::Missile(double x, double y, double size, double speed, double angle)
    : FlyingObject(x, y, size, 0, 0), angle(angle)
{
    double radians = angle * M_PI / 180.0;
    xSpeed = speed * sin(radians);
    ySpeed = -speed * cos(radians);
}

double Missile::getAngle() const {
    return angle;
}

bool Missile::move(double screenWidth, double screenHeight) {
    x += xSpeed;
    y += ySpeed;
    return (x < 0 || x > screenWidth || y < 0 || y > screenHeight);
}

std::string Missile::GetTypeName() const {
    return "Missile";
}
