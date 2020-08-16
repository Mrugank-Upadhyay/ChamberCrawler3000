#include "human.h"
#include "../player.h"

Human::Human(std::pair<int, int> position)
    : Enemy{"Human", "H", 140, 20, 20, position, true, 4, false} {}

std::string Human::attack(std::shared_ptr<Player> player) {
    return player->getStruckBy(this);
}

void Human::nextTurn() {}
