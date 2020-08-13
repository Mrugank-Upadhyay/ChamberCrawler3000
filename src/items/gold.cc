#include "../player.h"
#include "gold.h"

Gold::Gold(std::pair<int, int> position, int amount)
    : Item{"Gold", "G", position}, amount{amount}, canPickUp{true} {}

int Gold::getAmount() {
    return amount;
}

bool Gold::getCanPickUp() {
    return canPickUp;
}

void Gold::setCanPickUp(bool canPickUp) {
  this->canPickUp = canPickUp;
}

void Gold::apply(std::shared_ptr<Player> player) {
    player->applyItem(this);
}

std::string Gold::info() {
  return getType() + " " +
         "shown as " +
         getRep() + " " +
         "worth " + 
         std::to_string(getAmount());
}
