#include "orc.h"

Orc::Orc(std::pair<int, int> position)
    : Enemy{"Orc", "O", 180, 30, 25, position, true, randomGold(), true} {}

void Orc::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(shared_from_this());
}

void Orc::nextTurn() {}
