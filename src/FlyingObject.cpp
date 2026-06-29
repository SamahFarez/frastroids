#include "FlyingObject.h"
#include <cmath>

// Constructeur
FlyingObject::FlyingObject(double x, double y, double size, double xSpeed, double ySpeed)
    : x(x), y(y), size(size), xSpeed(xSpeed), ySpeed(ySpeed)
{
}

// Destructeur
FlyingObject::~FlyingObject()
{
}

// Getters
double FlyingObject::getX() const {
    return x;
}

double FlyingObject::getY() const {
    return y;
}

double FlyingObject::getSize() const {
    return size;
}

double FlyingObject::getXSpeed() const {
    return xSpeed;
}

double FlyingObject::getYSpeed() const {
    return ySpeed;
}

// Setters
void FlyingObject::setX(double x) {
    this->x = x;
}

void FlyingObject::setY(double y) {
    this->y = y;
}

void FlyingObject::setSize(double size) {
    this->size = size;
}

void FlyingObject::setXSpeed(double xSpeed) {
    this->xSpeed = xSpeed;
}

void FlyingObject::setYSpeed(double ySpeed) {
    this->ySpeed = ySpeed;
}

// Méthode de déplacement simple
bool FlyingObject::move() {
    x += xSpeed;
    y += ySpeed;
    return false;
}

// Méthode de déplacement avec réentrée à l'écran
bool FlyingObject::move(double screenWidth, double screenHeight) {
    x += xSpeed;
    y += ySpeed;
    
    // Gestion de la réentrée horizontale
    if (x < 0) {
        x = screenWidth;
    } else if (x > screenWidth) {
        x = 0;
    }
    
    // Gestion de la réentrée verticale
    if (y < 0) {
        y = screenHeight;
    } else if (y > screenHeight) {
        y = 0;
    }
    
    return false;  // Les astéroïdes ne sont pas détruits
}

// Static method to check collision between two objects
bool FlyingObject::collide(const FlyingObject& o1, const FlyingObject& o2) {
    // Calculate distance between centers
    double dx = o1.getX() - o2.getX();
    double dy = o1.getY() - o2.getY();
    double distance = sqrt(dx * dx + dy * dy);
    
    // Calculate sum of radii (size/2 for each object)
    double radius1 = o1.getSize() / 2.0;
    double radius2 = o2.getSize() / 2.0;
    double sumRadii = radius1 + radius2;
    
    // Collision occurs if distance <= sum of radii
    return distance <= sumRadii;
}

std::string FlyingObject::GetTypeName() const {
    return "FlyingObject";
}