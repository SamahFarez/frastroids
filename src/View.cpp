#include "View.h"
#include <cassert>

View::View(Framework* framework)
    : framework(framework)
{
    assert(framework != nullptr);
}

void View::refresh(const std::vector<std::shared_ptr<FlyingObject>>& objects, int score) const {
    for (const auto& obj : objects) {
        if (!obj) continue;

        std::string type = obj->GetTypeName();

        if (type == "Spaceship") {
            const Spaceship* ship = dynamic_cast<const Spaceship*>(obj.get());
            if (ship) {
                framework->drawAimLine(
                    static_cast<int>(ship->getX()),
                    static_cast<int>(ship->getY()),
                    static_cast<float>(ship->getAngle()),
                    framework->getScreenWidth(),
                    framework->getScreenHeight()
                );
                framework->drawShip(
                    static_cast<int>(ship->getX()),
                    static_cast<int>(ship->getY()),
                    static_cast<float>(ship->getAngle()),
                    static_cast<float>(ship->getShieldLevel()),
                    ship->GetInvincible()
                );
                framework->drawHUD(static_cast<float>(ship->getShieldLevel()), score);
            }
        } else if (type == "Asteroid") {
            const Asteroid* ast = dynamic_cast<const Asteroid*>(obj.get());
            if (ast) {
                framework->drawAsteroid(
                    static_cast<int>(ast->getX()),
                    static_cast<int>(ast->getY()),
                    static_cast<int>(ast->getSize())
                );
            }
        } else if (type == "Missile") {
            const Missile* miss = dynamic_cast<const Missile*>(obj.get());
            if (miss) {
                framework->drawMissile(
                    static_cast<int>(miss->getX()),
                    static_cast<int>(miss->getY())
                );
            }
        }
    }
}

void View::showEndScreen(bool victory) const {
    framework->drawEndScreen(victory);
}
