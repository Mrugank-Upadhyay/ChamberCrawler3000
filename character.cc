#include "character.h"

Character::Character(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position)
    : race{race}, rep{rep}, health{health}, atk{atk}, def{def}, position{position} {}

void Character::setHealth(int value) {
    health = value;
}

void Character::setAtk(int value) {
    atk = value;
}

void Character::setDef(int value) {
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

int Character::getHealth() {
    return health;
}

int Character::getAtk() {
    return atk;
}

int Character::getDef() {
    return def;
}

std::pair<int, int> Character::getPosition() {
    return position;
}