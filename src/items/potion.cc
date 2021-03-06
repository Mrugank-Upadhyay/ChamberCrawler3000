#include "../player.h"
#include "potion.h"

Potion::Potion(std::string type, std::string rep, std::pair<int, int> position, int hp, int atk, int def)
    : Item{type, rep, position}, hp{hp}, atk{atk}, def{def} {}

int Potion::getHP() {
    return hp;
}

int Potion::getATK() {
    return atk;
}

int Potion::getDEF() {
    return def;
}

void Potion::apply(std::shared_ptr<Player> player) {
    player->applyItem(this);
}

std::string Potion::info() {
  return getType() + " " +
         "shown as " +
         getRep() + " " +
         "changes hp:atk:def by " + 
         std::to_string(getHP()) + ":" +
         std::to_string(getATK()) + ":" +
         std::to_string(getDEF());
}
