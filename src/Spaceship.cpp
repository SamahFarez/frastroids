#include "Spaceship.h"

Spaceship::Spaceship(double x, double y, double size, double angle)
    : FlyingObject(x, y, size, 0.0, 0.0), angle(angle), shieldLevel(1.0),
      invincibilityEnd(std::chrono::steady_clock::now())
{
}

double Spaceship::getAngle() const {
    return angle;
}

void Spaceship::speedUp(double accelerationFactor) {
    double radians = angle * M_PI / 180.0;
    xSpeed += accelerationFactor * sin(radians);
    ySpeed += -accelerationFactor * cos(radians);
    double speed = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
    if (speed > 4.0) {
        xSpeed = xSpeed / speed * 4.0;
        ySpeed = ySpeed / speed * 4.0;
    }
}

void Spaceship::speedDown(double decelerationFactor) {
    double radians = angle * M_PI / 180.0;
    xSpeed -= decelerationFactor * sin(radians);
    ySpeed -= -decelerationFactor * cos(radians);
}

bool Spaceship::move(double screenWidth, double screenHeight) {
    xSpeed *= 0.97;
    ySpeed *= 0.97;
    return FlyingObject::move(screenWidth, screenHeight);
}

void Spaceship::rotate(double rAngle) {
    angle += rAngle;
    if (angle >= 360.0) angle -= 360.0 * floor(angle / 360.0);
    if (angle < 0.0)    angle += 360.0 * (1 + floor(-angle / 360.0));
}

double Spaceship::getShieldLevel() const {
    return shieldLevel;
}

void Spaceship::setShieldLevel(double value) {
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;
    shieldLevel = value;
}

bool Spaceship::GetInvincible() const {
    return std::chrono::steady_clock::now() < invincibilityEnd;
}

void Spaceship::SetInvincibleFor(double durationSeconds) {
    auto now = std::chrono::steady_clock::now();
    auto offset = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
        std::chrono::duration<double>(durationSeconds));
    invincibilityEnd = now + offset;
}

std::string Spaceship::GetTypeName() const {
    return "Spaceship";
}
