#include "../player.h"
#include "gold.h"

Gold::Gold(std::pair<int, int> position, int amount)
    : Item{"Gold", "G", position}, amount{amount} {}

int Gold::getAmount() {
    return amount;
}

void Gold::apply(Player * player) {
    player->applyItem(this);
}

std::string Gold::info() {
  return getType() + " " +
         "shown as " +
         getRep() + " " +
         "worth " + 
         std::to_string(getAmount());
}
