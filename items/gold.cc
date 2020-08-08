#include "../player.h"
#include "gold.h"

Gold::Gold(std::pair<int, int> position, int amount)
    : Item{"Gold", "G", position}, amount{amount} {}

int Gold::getAmount() {
    return amount;
}

void Gold::apply(std::shared_ptr<Player> player) {
    player->applyItem(shared_from_this());
}
