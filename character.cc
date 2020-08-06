#include "character.h"

Character::Character(std::string race, std::string rep, int hp, int atk, int def, std::pair<int, int> position)
    : race{race}, rep{rep}, hp{hp}, atk{atk}, def{def}, position{position} {}

void Character::setHP(int value) {
    hp = value;
}

void Character::setATK(int value) {
    atk = value;
}

void Character::setDEF(int value) {
    def = value;
}

void Character::setPosition(std::pair<int, int> pos) {
    position = pos;
}

std::string Character::getRace() {
    return race;
}

std::string Character::getRep() {
    return rep;
}

int Character::getHP() {
    return hp;
}

int Character::getATK() {
    return atk;
}

int Character::getDEF() {
    return def;
}

std::pair<int, int> Character::getPosition() {
    return position;
}

int Character::calculateDamage(int atk, int def) {
    int damage = static_cast<int>(ceil(((100 / (100 + def)) * atk)));
    return damage;
}