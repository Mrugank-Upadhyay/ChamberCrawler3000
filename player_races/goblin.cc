#include "goblin.h"
#include "../enemy.h"

Goblin::Goblin(std::pair<int, int> position)
  : Player{"Goblin", 110, 15, 20, position, 0, 110} {}

void Goblin::attack(std::shared_ptr<Enemy> enemy) {
  enemy->getStruckBy(std::make_shared<Goblin>(this));
  if(enemy->getHP() <= 0) addGold(5);
}
