#include "troll.h"
#include "../enemy.h"

Troll::Troll(std::pair<int, int> position)
  : Player("Troll", 120, 25, 15, position, 0, 120) {}

void Troll::nextTurn() {
  if(getHP() + 5 < getMaxHP()) setHP(getHP() + 5);
  else setHP(getMaxHP());
}

void Troll::nextTurn() {}
