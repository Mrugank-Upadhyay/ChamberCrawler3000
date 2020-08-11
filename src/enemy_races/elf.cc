#include "elf.h"
#include "../player.h"

Elf::Elf(std::pair<int, int> position)
    : Enemy{"Elf", "E", 140, 30, 10, position, true, 0, true} {
        setGold(randomGold());
}

void Elf::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(this);
    
    if (player->getRace() != "Drow") {
        player->getStruckBy(this);
    }
}

void Elf::nextTurn() {}
