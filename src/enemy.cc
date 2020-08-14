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

std::pair<int, int> Enemy::move() {
  auto position = getPosition();

  auto neighbours = cell->getObservers();
  int len = neighbours.size();
  std::vector<int> unOccupied;
  for(int i = 0; i < len; i++) {
    auto obsCell = dynamic_cast<Cell *>(neighbours[i]);
    if(!obsCell->getOccupied()) {
      unOccupied.push_back(i);
    }
  }
  int chosen = rand() % unOccupied.size();
  auto dest = dynamic_cast<Cell *>(neighbours[unOccupied[chosen]]);
  cell->moveCharacter(dest);

  return position;
}

void Enemy::getStruckBy(Shade * shade) {
    int damage = calculateDamage(shade->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);

    // Will this need to notify cell when health == 0?
    // if so, how?
    transferGold(shade);
    setHostile(true);
    std::cout << " PC deals " << damage << "damage to " << getRep()
              << " (" << getHP() << " HP).";
}

void Enemy::getStruckBy(Drow * drow) {
    int damage = calculateDamage(drow->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(drow);
    setHostile(true);
    std::cout << " PC deals " << damage << "damage to " << getRep()
              << " (" << getHP() << " HP).";
}

void Enemy::getStruckBy(Vampire * vampire) {
    int damage = calculateDamage(vampire->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(vampire);
    setHostile(true);
    std::cout << " PC deals " << damage << "damage to " << getRep()
              << " (" << getHP() << " HP).";
}

void Enemy::getStruckBy(Troll * troll) {
    int damage = calculateDamage(troll->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(troll);
    setHostile(true);
    std::cout << " PC deals " << damage << "damage to " << getRep()
              << " (" << getHP() << " HP).";
}

void Enemy::getStruckBy(Goblin * goblin) {
    int damage = calculateDamage(goblin->getTmpATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(goblin);
    setHostile(true);
    std::cout << " PC deals " << damage << "damage to " << getRep()
              << " (" << getHP() << " HP).";
}

void Enemy::nextTurn() {
  // if player in vicinity attack instead of moving
  auto observers = cell->getObservers();
  for(auto obs: observers) {
    auto obsCell = dynamic_cast<Cell *>(obs);
    if(obsCell->getPlayer() != nullptr && getHostile()) {
      attack(obsCell->getPlayer());
      return;
    }
  }
  if(!isStopped) {
    move();
  }
}

int Enemy::randomGold() {
    return (rand() % 2);
}

void Enemy::transferGold(Player * player) {
    if ((giveGold == true) && (getHP() == 0)) {
        player->addGold(gold);
        gold = 0;
    }
}

std::string Enemy::info() {
  std::string str = Character::info();
  if(getHostile()) {
    str += " who is hostile";
  }
  else {
    str += " who is not hostile";
  }
  str += " and has " + std::to_string(getGold()) + " gold";
  
  //Remove after
  str += " and has the cell: " + cell->info();
  return str;
}
