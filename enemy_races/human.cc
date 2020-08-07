#include "human.h"

Human::Human(std::pair<int, int> position)
    : Enemy{"Human", "H", 140, 20, 20, position, true, 4, false} {}

void Human::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(shared_from_this());
}

void Human::nextTurn() {}
