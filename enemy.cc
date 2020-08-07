#include "player.h"
#include "enemy.h"

Enemy::Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold)
    : Character{race, rep, health, atk, def, position}, isHostile{hostile}, gold{gold}, giveGold{giveGold} {}

void Enemy::setHostile(bool hostile) {
    isHostile = hostile;
}

void Enemy::setGold(int value) {
    gold = value;
}

void Enemy::setCell(Cell * cell) {
    this->cell = cell;
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

std::pair<int, int> Enemy::move(int x, int y) {
    setPosition(std::pair<int, int>(x, y));
    return getPosition();
}

void Enemy::getStruckBy(std::shared_ptr<Shade> shade) {
    int damage = calculateDamage(shade->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);

    // Will this need to notify cell when health == 0?
    // if so, how?
    transferGold(shade);
}

void Enemy::getStruckBy(std::shared_ptr<Drow> drow) {
    int damage = calculateDamage(drow->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(drow);
}

void Enemy::getStruckBy(std::shared_ptr<Vampire> vampire) {
    int damage = calculateDamage(vampire->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(vampire);
}

void Enemy::getStruckBy(std::shared_ptr<Troll> troll) {
    int damage = calculateDamage(troll->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(troll);
}

void Enemy::getStruckBy(std::shared_ptr<Goblin> goblin) {
    int damage = calculateDamage(goblin->getATK(), getDEF());
    int health = getHP();
    health -= damage;
    setHP(health);
    transferGold(goblin);
}

int Enemy::randomGold() {
    return (rand() % 2);
}

void Enemy::transferGold(std::shared_ptr<Player> player) {
    if ((giveGold == true) && (getHP() == 0)) {
        player->addGold(gold);
        gold = 0;
    }
}