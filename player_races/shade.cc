#include "shade.h"

Shade::Shade(std::pair<int, int> position)
    : Player{"Shade", 125, 25, 25, position, 0, false} {}

void Shade::attack(std::shared_ptr<Enemy> enemy) {
    enemy->getStruckBy(std::make_shared<Shade>(*this));
}
