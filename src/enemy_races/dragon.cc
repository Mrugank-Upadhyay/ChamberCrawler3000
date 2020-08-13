#include "dragon.h"
#include "../player.h"
#include "../cell.h"

// If attacked, make all future Dragons hostile!
Dragon::Dragon(std::pair<int, int> position, std::shared_ptr<Cell> goldCell)
  : Enemy{"Dragon", "D", 150, 20, 20, position, false, 6, false}, goldCell{goldCell} 
{}

std::shared_ptr<Cell> Dragon::getGoldCell() {
  return goldCell;
}

void Dragon::setGoldCell(std::shared_ptr<Cell> cell) {
  goldCell = cell;
}

std::pair<int, int> Dragon::move() {
  auto previous = getPosition();

  auto goldNeighours = goldCell->getObservers();
  auto neighbours = getCell()->getObservers();
  std::vector<std::shared_ptr<Cell>> intersect;
  for(auto obs1: goldNeighours) {
    for(auto obs2: neighbours) {
      if(obs1 == obs2) {
        auto obsCell =
          std::dynamic_pointer_cast<Cell>(obs1);
        if(!obsCell->getOccupied()) {
          intersect.push_back(obsCell);
        }
      }
    }
  }

  int len = intersect.size();
  if(len != 0) {
    auto dest = intersect[rand() % len];
    getCell()->moveCharacter(dest);
  }

  return previous;
}

void Dragon::attack(std::shared_ptr<Player> player) {
  player->getStruckBy(this);
}
