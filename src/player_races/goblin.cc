#include "goblin.h"
#include "../enemy.h"
#include "../enemy_races/orc.h"

#include <iostream>

Goblin::Goblin(std::pair<int, int> position)
  : Player{"Goblin", 110, 15, 20, position, 0, 110} {}

void Goblin::attack(std::shared_ptr<Enemy> enemy) {
  enemy->getStruckBy(this);
  if(enemy->getHP() <= 0) addGold(5);
}

void Goblin::getStruckBy(Orc *enemy) {
  int damage = calculateDamage(enemy->getATK(), getTmpDEF());
  setHP(getHP() - damage * 1.5);
  std::cout << " O deals " << damage << " times 1.5 to PC ("
            << getHP() << " HP).";
}
