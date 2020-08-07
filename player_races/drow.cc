#include "drow.h"
#include "../enemy.h"
#include "../items/potion.h"

Drow::Drow(std::pair<int, int> position)
  : Player{"Drow", 150, 25, 15, position, 0, 150} {}

void Drow::applyItem(std::shared_ptr<Potion> potion) {
  int nextHP = getHP() + potion->getHP() * 1.5;
  setHP(nextHP < getMaxHP() ? nextHP : getMaxHP());
  int nextATK = getTmpATK() + potion->getATK() * 1.5;
  setTmpATK(nextATK > 0 ? nextATK : 0);
  int nextDEF = getTmpDEF() + potion->getDEF() * 1.5;
  setTmpDEF(nextDEF > 0 ? nextDEF : 0);
}

void Drow::attack(std::shared_ptr<Enemy> enemy) {
  enemy->getStruckBy(std::make_shared<Drow>(this));
}

void Drow::nextTurn() {}
