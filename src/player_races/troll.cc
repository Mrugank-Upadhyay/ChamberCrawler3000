#include "troll.h"
#include "../enemy.h"

Troll::Troll(std::pair<int, int> position)
  : Player("Troll", 120, 25, 15, position, 0, 120) {}

std::string Troll::attack(std::shared_ptr<Enemy> enemy) {
  return enemy->getStruckBy(this);
}

void Troll::nextTurn() {
  if(getHP() + 5 < getMaxHP()) setHP(getHP() + 5);
  else setHP(getMaxHP());
}
