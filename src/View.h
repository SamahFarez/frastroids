#ifndef VIEW_H
#define VIEW_H

#include "Framework.h"
#include "FlyingObject.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Missile.h"
#include <memory>
#include <vector>
#include <string>

class View {
private:
    Framework* framework;

public:
    View(Framework* framework);

    void refresh(const std::vector<std::shared_ptr<FlyingObject>>& objects, int score) const;

    void showEndScreen(bool victory) const;
};

#endif // VIEW_H
