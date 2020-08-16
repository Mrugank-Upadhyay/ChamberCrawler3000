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
#include <string>
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

  if (getRace() != "Vampire") {
    setHP(nextHP < maxHP ? nextHP : maxHP);
  }
  else {
    setHP(nextHP);
  }
  int nextATK = getTmpATK() + potion->getATK();
  setTmpATK(nextATK > 0 ? nextATK : 0);
  int nextDEF = getTmpDEF() + potion->getDEF();
  setTmpDEF(nextDEF > 0 ? nextDEF : 0);
}

void Player::applyItem(Gold * gold) {
  addGold(gold->getAmount());
}

std::string Player::getStruckBy(Human * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Dwarf * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Elf * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Orc * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Dragon * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Merchant * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

std::string Player::getStruckBy(Halfling * enemy) {
  int damage = calculateDamage(enemy->getATK(), tmpDEF);
  setHP(getHP() - damage);
  std::string message = enemy->getRep() + " deals " + std::to_string(damage) + " damage to PC.";
  return message;
}

void Player::nextTurn() {}
