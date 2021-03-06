#include "dwarf.h"
#include "../player.h"

Dwarf::Dwarf(std::pair<int, int> position)
    : Enemy{"Dwarf", "W", 100, 20, 30, position, true, 0, true} {
        setGold(randomGold());
}

std::string Dwarf::attack(std::shared_ptr<Player> player) {
    return player->getStruckBy(this);
}

void Dwarf::nextTurn() {}
