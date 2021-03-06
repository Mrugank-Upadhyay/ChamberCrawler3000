#include "orc.h"
#include "../player.h"

Orc::Orc(std::pair<int, int> position)
    : Enemy{"Orc", "O", 180, 30, 25, position, true, 0, true} {
        setGold(randomGold());
}

std::string Orc::attack(std::shared_ptr<Player> player) {
    return player->getStruckBy(this);
}

void Orc::nextTurn() {}
