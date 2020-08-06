#include "elf.h"

Elf::Elf(std::pair<int, int> position)
    : Enemy{"Elf", "E", 140, 30, 10, position, true, randomGold(), true} {}

void attack(std::shared_ptr<Player> player) {
    player->getStruckBy(this);
    
    if (player->getRace() != "Drow") {
        player->getStruckBy(this);
    }
}