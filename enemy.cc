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

bool Enemy::getHostile() {
    return isHostile;
}

int Enemy::getGold() {
    return gold;
}

std::pair<int, int> Enemy::move(int x, int y) {
    setPosition(std::pair<int, int>(x, y));
    return getPosition();
}

void Enemy::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(*this);
}

void Enemy::getStruckBy(std::shared_ptr<Shade> shade) {
    int damage = calculateDamage(shade->getAtk(), getDef());
    int health = getHealth();
    health -= damage;
    setHealth(health);

    // Will this need to notify cell when health == 0?
    // if so, how?
    transferGold(shade, std::make_shared<Enemy>(*this));
}

void Enemy::getStruckBy(std::shared_ptr<Drow> drow) {
    int damage = calculateDamage(drow->getAtk(), getDef());
    int health = getHealth();
    health -= damage;
    setHealth(health);
    transferGold(drow, std::make_shared<Enemy>(*this));
}

void Enemy::getStruckBy(std::shared_ptr<Vampire> vampire) {
    int damage = calculateDamage(vampire->getAtk(), getDef());
    int health = getHealth();
    health -= damage;
    setHealth(health);
    transferGold(vampire, std::make_shared<Enemy>(*this));
}

void Enemy::getStruckBy(std::shared_ptr<Troll> troll) {
    int damage = calculateDamage(troll->getAtk(), getDef());
    int health = getHealth();
    health -= damage;
    setHealth(health);
    transferGold(troll, std::make_shared<Enemy>(*this));
}

void Enemy::getStruckBy(std::shared_ptr<Goblin> goblin) {
    int damage = calculateDamage(goblin->getAtk(), getDef());
    int health = getHealth();
    health -= damage;
    setHealth(health);
    transferGold(goblin, std::make_shared<Enemy>(*this));
}

int Enemy::randomGold() {
    return (rand() % 2);
}

void Enemy::transferGold(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy) {
    if ((giveGold == true) && (enemy->getHealth() == 0)) {
        player->setGold(player->getGold() + enemy->gold);
        enemy->gold = 0;
    }
}