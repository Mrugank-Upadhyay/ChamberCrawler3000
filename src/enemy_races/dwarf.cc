#include "dwarf.h"
#include "../player.h"

Dwarf::Dwarf(std::pair<int, int> position)
// can we even add randomGold in the MIL like this? As a function
    : Enemy{"Dwarf", "W", 100, 20, 30, position, true, 0, true} {
        setGold(randomGold());
}

void Dwarf::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(this);
}

void Dwarf::nextTurn() {}
