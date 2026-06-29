#ifndef ASTEROID_H
#define ASTEROID_H

#include "FlyingObject.h"
#include <memory>

class Asteroid : public FlyingObject {
private:
    double nbExplosionsLeft;

public:
    Asteroid(double x, double y, double size, double xSpeed, double ySpeed, double nbExplosionsLeft = 2.0);

    double getExplosionsLeft() const;

    /**
     * @brief Applique une explosion à l'astéroïde.
     *
     * Si l'astéroïde peut encore exploser, sa taille est réduite et un
     * nouvel astéroïde est créé.
     *
     * @param xSpeed Vecteur de vitesse en X du nouvel astéroïde (s'il est créé).
     * @param ySpeed Vecteur de vitesse en Y du nouvel astéroïde (s'il est créé).
     *
     * @return shared_ptr<Asteroid>
     * - Si l'astéroïde peut encore exploser : pointeur vers le nouvel astéroïde,
     *   avec la même position et le vecteur de vitesse donné en paramètre.
     * - Sinon : nullptr.
     */
    std::shared_ptr<Asteroid> Explode(double xSpeed, double ySpeed);

    std::string GetTypeName() const override;
};

#endif // ASTEROID_H
