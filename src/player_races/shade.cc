#include "shade.h"
#include "../enemy.h"

Shade::Shade(std::pair<int, int> position)
    : Player{"Shade", 125, 25, 25, position, 0, 125} {}

std::string Shade::attack(std::shared_ptr<Enemy> enemy) {
    return enemy->getStruckBy(this);
}

void Shade::nextTurn() {}
