#include "cell.h"
#include "player.h"
#include "./player_races/shade.h"
#include "./player_races/drow.h"
#include "./player_races/vampire.h"
#include "./player_races/troll.h"
#include "./player_races/goblin.h"
#include "enemy.h"

Enemy::Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold)
    : Character{race, rep, health, atk, def, position}, isHostile{hostile}, gold{gold}, giveGold{giveGold} {}

void Enemy::setHostile(bool hostile) {
    isHostile = hostile;
}

void Enemy::setGold(int value) {
    gold = value;
}

void Enemy::setCell(std::shared_ptr<Cell> cell) {
    this->cell = cell;
}

bool Enemy::getHostile() {
    return isHostile;
}

int Enemy::getGold() {
    return gold;
}

std::shared_ptr<Cell> Enemy::getCell() {
    return cell;
}

std::pair<int, int> Enemy::move(int x, int y) {
    setPosition(std::pair<int, int>(x, y));
    return getPosition();
}

void Enemy::getStruckBy(Shade * shade) {
    int damage = calculateDamage(shade->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);

    // Will this need to notify cell when health == 0?
    // if so, how?
    transferGold(shade);
}

void Enemy::getStruckBy(Drow * drow) {
    int damage = calculateDamage(drow->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(drow);
}

void Enemy::getStruckBy(Vampire * vampire) {
    int damage = calculateDamage(vampire->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(vampire);
}

void Enemy::getStruckBy(Troll * troll) {
    int damage = calculateDamage(troll->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(troll);
}

void Enemy::getStruckBy(Goblin * goblin) {
    int damage = calculateDamage(goblin->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(goblin);
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