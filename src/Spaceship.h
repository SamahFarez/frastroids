#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "FlyingObject.h"
#include <cmath>
#include <chrono>

class Spaceship : public FlyingObject {
private:
    double angle;  // en degrés, 0 = nord
    double shieldLevel;
    std::chrono::steady_clock::time_point invincibilityEnd;

public:
    Spaceship(double x, double y, double size, double angle);

    double getAngle() const;

    void speedUp(double accelerationFactor);
    void speedDown(double decelerationFactor);
    void rotate(double rAngle);

    double getShieldLevel() const;
    void setShieldLevel(double value);

    bool move(double screenWidth, double screenHeight) override;

    bool GetInvincible() const;
    void SetInvincibleFor(double durationSeconds);

    std::string GetTypeName() const override;
};

#endif // SPACESHIP_H
