#include "cell.h"

Cell::Cell(std::string type, std::string rep, std::pair<int, int> position)
  : type{type}, rep{rep}, position{position}, player{nullptr}, enemy{nullptr}, item{nullptr} {}

std::string & Cell::getType() { return type; }

std::string & Cell::getRep() { return rep; }
void Cell::setRep(std::string &rep) { this->rep = rep; }

std::pair<int, int> Cell::getPosition() { return position; }
void Cell::setPosition(std::pair<int, int> position) { this->position = position; }

std::shared_ptr<Player> Cell::getPlayer() { return player; }
std::shared_ptr<Enemy> Cell::getEnemy() { return enemy; }
void Cell::setCharacter(std::shared_ptr<Player> player) { 
  this->player = player;
  this->enemy = nullptr;
}
void Cell::setCharacter(std::shared_ptr<Enemy> enemy) {
  this->enemy = enemy;
  this->player = nullptr;
}

std::shared_ptr<Item> Cell::getItem() { return item; }
void Cell::setItem(std::shared_ptr<Item> item) { this->item = item; }

std::vector<std::shared_ptr<Observer>> & Cell::getObservers() { return observers; }

void Cell::notify(std::shared_ptr<Subject> whoNotified) {
  std::shared_ptr<Cell> otherCell = std::make_shared<Cell>(whoNotified);
  if(enemy != nullptr && otherCell->getPlayer() != nullptr) {
    enemy->attack(otherCell->getPlayer());
  }
}
