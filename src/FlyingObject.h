#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include <string>

class FlyingObject {
protected:
    double x;      // position horizontale
    double y;      // position verticale
    double size;   // taille (diamètre)
    double xSpeed; // vitesse horizontale
    double ySpeed; // vitesse verticale

public:
    FlyingObject(double x, double y, double size, double xSpeed, double ySpeed);
    virtual ~FlyingObject();

    double getX() const;
    double getY() const;
    double getSize() const;
    double getXSpeed() const;
    double getYSpeed() const;

    void setX(double x);
    void setY(double y);
    void setSize(double size);
    void setXSpeed(double xSpeed);
    void setYSpeed(double ySpeed);

    /**
     * @brief Déplace l'objet selon son vecteur vitesse.
     */
    virtual bool move();

    /**
     * @brief Déplace l'objet et le fait réapparaître de l'autre côté si il sort de l'écran.
     */
    virtual bool move(double screenWidth, double screenHeight);

    virtual std::string GetTypeName() const;

    /**
     * @brief Détermine si deux objets sphériques entrent en collision.
     *
     * La collision est détectée si la distance entre les centres des objets
     * est inférieure ou égale à la somme de leurs rayons.
     *
     * @param o1 Premier objet à tester.
     * @param o2 Second objet à tester.
     * @return true si les deux objets se touchent.
     */
    static bool collide(const FlyingObject& o1, const FlyingObject& o2);
};

#endif // FLYINGOBJECT_H
