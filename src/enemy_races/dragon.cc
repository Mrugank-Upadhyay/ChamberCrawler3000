#include "dragon.h"
#include "../player.h"
#include "../cell.h"
#include <iostream>

// If attacked, make all future Dragons hostile!
Dragon::Dragon(std::pair<int, int> position, Cell * goldCell)
  : Enemy{"Dragon", "D", 150, 20, 20, position, false, 6, false}, goldCell{goldCell} 
{}

Cell * Dragon::getGoldCell() {
  return goldCell;
}

void Dragon::setGoldCell(Cell * cell) {
  goldCell = cell;
}

void Dragon::move() {
  auto goldNeighours = goldCell->getObservers();

  auto neighbours = getCell()->getObservers();
  std::vector<Cell *> intersect;
  for(auto obs1: goldNeighours) {
    for(auto obs2: neighbours) {
      if(obs1 == obs2) {
        auto obsCell =
          dynamic_cast<Cell *>(obs1);
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
}

std::string Dragon::attack(std::shared_ptr<Player> player) {
  return player->getStruckBy(this);
}
