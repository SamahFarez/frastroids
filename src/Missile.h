#ifndef MISSILE_H
#define MISSILE_H

#include "FlyingObject.h"

class Missile : public FlyingObject {
private:
    double angle;

public:
    /**
     * @param x Position initiale sur l'axe X de l'écran.
     * @param y Position initiale sur l'axe Y de l'écran.
     * @param size Diamètre du missile.
     * @param speed Vitesse de déplacement du missile.
     * @param angle Orientation du missile en degrés.
     */
    Missile(double x, double y, double size, double speed, double angle);

    double getAngle() const;

    /**
     * @brief Déplace le missile selon sa vitesse et son orientation.
     * @return true si le missile sort des limites de l'écran.
     */
    bool move(double screenWidth, double screenHeight) override;

    std::string GetTypeName() const override;
};

#endif // MISSILE_H
