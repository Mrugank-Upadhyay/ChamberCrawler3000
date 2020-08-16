#include "../player.h"
#include "../cell.h"
#include "elf.h"

Elf::Elf(std::pair<int, int> position)
    : Enemy{"Elf", "E", 140, 30, 10, position, true, 0, true} {
        setGold(randomGold());
}

std::string Elf::attack(std::shared_ptr<Player> player) {
    std::string message = player->getStruckBy(this);
    
    if (player->getRace() != "Drow") {
        message += "and again " + player->getStruckBy(this) + ". ";
    }

    return message;
}

void Elf::nextTurn() {}
