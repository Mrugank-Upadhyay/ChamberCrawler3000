#include "player.h"

#include "cell.h"

#include "enemy.h"
#include "enemy_races/human.h"
#include "enemy_races/dwarf.h"
#include "enemy_races/elf.h"
#include "enemy_races/orc.h"
#include "enemy_races/merchant.h"
#include "enemy_races/dragon.h"
#include "enemy_races/halfling.h"

#include "item.h"
#include "items/gold.h"
#include "items/potion.h"

#include <iostream>

Player::Player(std::string race, int hp, int atk, int def, 
    std::pair<int, int> position, int gold, int maxHP)
  : Character{race, "@", hp, atk, def, position}, cell{nullptr}, gold{gold},
    maxHP{maxHP}, tmpATK{atk}, tmpDEF{def}, bagActive{false} {}

Cell * Player::getCell() const { return cell; }
void Player::setCell(Cell * cell) { this->cell = cell; }

int Player::getGold() const { return gold; }
void Player::addGold(int gold) { this->gold += gold; }

int Player::getMaxHP() const { return maxHP; }
void Player::setMaxHP(int maxHP) { this->maxHP = maxHP; }

int Player::getTmpATK() const { return tmpATK; }
void Player::setTmpATK(int tmpATK) { this->tmpATK = tmpATK; }

int Player::getTmpDEF() const { return tmpDEF; }
void Player::setTmpDEF(int tmpDEF) { this->tmpDEF = tmpDEF; }

bool Player::isTurnFinished() const { return turnFinished; }
void Player::setTurnedFinished(bool turnFinished) 
{ this->turnFinished = turnFinished; }

std::vector<std::shared_ptr<Item>> Player::getBag() { return bag; }

void Player::addToBag(std::shared_ptr<Item> item) {
  bag.push_back(item);
}

void Player::removeFromBag(int item) {
  if(1 <= item && item <= bag.size()) bag.erase(bag.begin()+item-1);
}

bool Player::isBagActive() const {
  return bagActive;
}

std::pair<int, int> Player::move(std::pair<int,int> position) {
  auto previous = getPosition();

  auto dest = cell;
  auto observers = cell->getObservers();
  for(auto obs: observers) {
    auto obsCell = dynamic_cast<Cell *>(obs);
    if(obsCell->getPosition() == position) {
      dest = obsCell;
      break;
    }
  }
  cell->moveCharacter(dest);
  
  return previous;
}

void Player::applyItem(Potion * potion) {
  int nextHP = getHP() + potion->getHP();
  setHP(nextHP < maxHP ? nextHP : maxHP);
  int nextATK = getTmpATK() + potion->getATK();
  setTmpATK(nextATK > 0 ? nextATK : 0);
  int nextDEF = getTmpDEF() + potion->getDEF();
  setTmpDEF(nextDEF > 0 ? nextDEF : 0);
}

void Player::applyItem(Gold * gold) {
  addGold(gold->getAmount());
}

void Player::getStruckBy(Human * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Dwarf * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Elf * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Orc * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Dragon * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Merchant * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::getStruckBy(Halfling * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::cout << " " << enemy->getRep() << " deals "
            << damage << " damage to PC.";
}

void Player::nextTurn() {}

std::string Player::info() {
  auto str = Character::info() + " " +
         "and has " +
         std::to_string(getGold()) + " gold " +
         "with current maxHP:tmpATK:tmpDEF of " +
         std::to_string(getMaxHP()) + ":" +
         std::to_string(getTmpATK()) + ":" +
         std::to_string(getTmpDEF()) + " ";

  str += "plus a bag with:";
  for(auto item_ptr: getBag()) {
    str += " " + item_ptr->info() + ",";
  }
  if(getBag().size() == 0) str += " nothing";
  return str;
}
