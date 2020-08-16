#include "cell.h"
#include "player.h"
#include "./player_races/shade.h"
#include "./player_races/drow.h"
#include "./player_races/vampire.h"
#include "./player_races/troll.h"
#include "./player_races/goblin.h"
#include "enemy.h"

#include <iostream>

bool Enemy::isStopped = false;

Enemy::Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold)
    : Character{race, rep, health, atk, def, position}, isHostile{hostile}, gold{gold}, giveGold{giveGold} {}

void Enemy::setStopped(bool stopped) {
    isStopped = stopped;
}

void Enemy::setHostile(bool hostile) {
    isHostile = hostile;
}

void Enemy::setGold(int value) {
    gold = value;
}

void Enemy::setCell(Cell * cell) {
    this->cell = cell;
}

bool Enemy::getStopped() { 
    return isStopped;
}

bool Enemy::getHostile() {
    return isHostile;
}

int Enemy::getGold() {
    return gold;
}

Cell * Enemy::getCell() {
    return cell;
}


bool Enemy::distanceLessThanTwo(std::pair<int, int> position) {
    int x = getPosition().first;
    int y = getPosition().second;
    int dx = position.first;
    int dy = position.second;
    if ((abs(x - dx) <= 1) && (abs(y - dy) <= 1)) {
        return true;
    }

    return false;
}

void Enemy::move() {

  auto neighbours = cell->getObservers();
  int len = neighbours.size();
  std::vector<int> unOccupied;
  Cell * destCell = cell;
  for(int i = 0; i < len; i++) {
    auto obsCell = dynamic_cast<Cell *>(neighbours.at(i));
    if((!obsCell->getOccupied()) && (obsCell->getType() != "Exit") &&
        (distanceLessThanTwo(obsCell->getPosition()))) {
      unOccupied.push_back(i);
    }
  }
  if(unOccupied.size() > 0) {
    int chosen = rand() % unOccupied.size();
    destCell = dynamic_cast<Cell *>(neighbours.at(unOccupied.at(chosen)));
  }
  cell->moveCharacter(destCell);
}

std::string Enemy::getStruckBy(Shade * shade) {
    int damage = calculateDamage(shade->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(shade);
    setHostile(true);
    std::string message = "PC deals " + std::to_string(damage) + " damage to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
    return message;
}

std::string Enemy::getStruckBy(Drow * drow) {
    int damage = calculateDamage(drow->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(drow);
    setHostile(true);
    std::string message = "PC deals " + std::to_string(damage) + " damage to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
    return message;
}

std::string Enemy::getStruckBy(Vampire * vampire) {
    int damage = calculateDamage(vampire->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(vampire);
    setHostile(true);
    std::string message = "PC deals " + std::to_string(damage) + " damage to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
    return message;
}

std::string Enemy::getStruckBy(Troll * troll) {
    int damage = calculateDamage(troll->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(troll);
    setHostile(true);
    std::string message = "PC deals " + std::to_string(damage) + " damage to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
    return message;
}

std::string Enemy::getStruckBy(Goblin * goblin) {
    int damage = calculateDamage(goblin->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(goblin);
    setHostile(true);
    std::string message = "PC deals " + std::to_string(damage) + " damage to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
    return message;
}

void Enemy::nextTurn() {}

int Enemy::randomGold() {
    return (rand() % 2);
}

void Enemy::transferGold(Player * player) {
    if ((giveGold == true) && (getHP() == 0)) {
        player->addGold(gold);
        gold = 0;
    }
}
