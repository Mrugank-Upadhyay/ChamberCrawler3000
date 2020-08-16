#include "goblin.h"
#include "../enemy.h"
#include "../enemy_races/orc.h"

#include <iostream>

Goblin::Goblin(std::pair<int, int> position)
  : Player{"Goblin", 110, 15, 20, position, 0, 110} {}

std::string Goblin::attack(std::shared_ptr<Enemy> enemy) {
  std::string message = enemy->getStruckBy(this);
  if(enemy->getHP() <= 0) addGold(5);
  return message;
}

std::string Goblin::getStruckBy(Orc *enemy) {
  int damage = calculateDamage(enemy->getATK(), getTmpDEF()) * 1.5;
  setHP(getHP() - damage);

  return enemy->getRep() + " deals " + std::to_string(damage) + " to PC (" + std::to_string(getHP()) + " HP). ";
}
