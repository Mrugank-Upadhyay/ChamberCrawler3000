#include "gold.h"

Gold::Gold(std::pair<int, int> position, int amount)
    : Item{"Gold", "G", position}, amount{amount} {}

int Gold::getAmount() {
    return amount;
}

void Gold::apply(Player p) {
    p->applyItem(std::make_shared<Gold>(*this));
}
