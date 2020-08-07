#include "elf.h"

Elf::Elf(std::pair<int, int> position)
    : Enemy{"Elf", "E", 140, 30, 10, position, true, randomGold(), true} {}

void Elf::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(shared_from_this());
    
    if (player->getRace() != "Drow") {
        player->getStruckBy(shared_from_this());
    }
}

void Elf::nextTurn() {}
