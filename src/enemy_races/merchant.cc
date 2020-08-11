#include "merchant.h"
#include "../player.h"

// If attacked, make all future merchants hostile!
Merchant::Merchant(std::pair<int, int> position)
    : Enemy{"Merchant", "M", 30, 70, 5, position, false, 4, false} {}

void Merchant::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(this);
}

void Merchant::nextTurn() {}