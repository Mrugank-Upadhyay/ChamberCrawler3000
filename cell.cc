#include "cell.h"

Cell::Cell(std::string type, std::string rep, std::pair<int, int> position)
  : type{type}, rep{rep}, position{position}, character{nullptr}, item{nullptr} {}

std::string & Cell::getType() { return type; }

std::string & Cell::getRep() { return rep; }
void Cell::setRep(std::string &rep) { this->rep = rep; }

std::pair<int, int> Cell::getPosition() { return position; }
void Cell::setPosition(std::pair<int, int> position) { this->position = position; }

std::shared_ptr<Character> Cell::getCharacter() { return character; }
void Cell::setCharacter(std::shared_ptr<Character> character) { this->character = character; }

std::shared_ptr<Item> Cell::getItem() { return item; }
void Cell::setItem(std::shared_ptr<Item> item) { this->item = item; }

std::vector<std::shared_ptr<Observer>> & Cell::getObservers() { return observers; }

void Cell::notify(std::shared_ptr<Subject> whoNotified) {
  std::shared_ptr<Cell> otherCell = std::make_shared<Cell>(whoNotified);
  if(character != nullptr && otherCell->getCharacter() != nullptr) {
    character->attack(otherCell->getCharacter());
  }
}
