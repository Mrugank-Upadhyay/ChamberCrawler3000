#include "dwarf.h"

Dwarf::Dwarf(std::pair<int, int> position)
// can we even add randomGold in the MIL like this? As a function
    : Enemy{"Dwarf", "W", 100, 20, 30, position, true, randomGold(), true} {}

void Dwarf::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(shared_from_this());
}

void Dwarf::nextTurn() {}
