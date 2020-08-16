#include "cell.h"
#include <iostream>

Cell::Cell(std::string type, std::string rep, std::pair<int, int> position)
  : type{type}, rep{rep}, position{position}, player{nullptr}, enemy{nullptr}, item{nullptr} {}

std::string & Cell::getType() { return type; }

std::string Cell::getRep() { 
  std::string result_rep = rep;
  if(player != nullptr) {
    result_rep = player->getRep();
  }
  else if(enemy != nullptr) {
    result_rep = enemy->getRep();
  }
  else if(item != nullptr) {
    result_rep = item->getRep();
  }
  return result_rep;
}
void Cell::setRep(std::string rep) { this->rep = rep; }

std::pair<int, int> Cell::getPosition() { return position; }
void Cell::setPosition(std::pair<int, int> position) { this->position = position; }

void Cell::setOccupied(bool isOccupied) { this->isOccupied = isOccupied; }
bool Cell::getOccupied() { return isOccupied; }

std::shared_ptr<Player> Cell::getPlayer() { return player; }
std::shared_ptr<Enemy> Cell::getEnemy() { 
  return enemy; }

void Cell::setCharacter(std::shared_ptr<Player> player) { 
  this->player = player;
  this->enemy = nullptr;
  isOccupied = (player == nullptr) ? false : true;
}

void Cell::setCharacter(std::shared_ptr<Enemy> enemy) {
  this->enemy = enemy;
  this->player = nullptr;
  isOccupied = (enemy == nullptr) ? false : true;
}

void Cell::setNullCharacter() {
  player = nullptr;
  enemy = nullptr;
  isOccupied = false;
}

void Cell::moveCharacter(Cell * dest) {
  if(player != nullptr) {
    player->setCell(dest);
    player->setPosition(dest->getPosition());
    dest->setCharacter(player);
    dest->notifyObservers();
    player = nullptr;
    isOccupied = false;
  }
  else if(enemy != nullptr) {
    enemy->setCell(dest);
    enemy->setPosition(dest->getPosition());
    dest->setCharacter(enemy);
    enemy = nullptr;
    isOccupied = false;
  }
}

std::shared_ptr<Item> Cell::getItem() { return item; }
void Cell::setItem(std::shared_ptr<Item> item) { 
  this->item = item; 
  isOccupied = (item == nullptr) ? false : true;
}

std::vector<Observer *> & Cell::getObservers() { return observers; }

void Cell::notify(Subject * whoNotified) {
  auto other  = dynamic_cast<Cell *>(whoNotified);
  if(enemy != nullptr && other->getPlayer() != nullptr) {
    enemy->attack(other->getPlayer());
  }
}

std::string Cell::info() {
  std::string info = "type: " + type + " rep: " + rep + 
                     " position: (" + std::to_string(position.first) + 
                     ", " + std::to_string(position.second) + ") ";
  (player != nullptr) ? info.append(player->info() + " ") : info;
  (enemy != nullptr) ? info.append(enemy->info() + " ") : info;
  (item != nullptr) ? info.append(item->info() + " ") : info;

  return info;
}
