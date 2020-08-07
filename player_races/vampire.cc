#include "vampire.h"

Vampire::Vampire(std::pair<int, int> position) 
    : Player{"Vampire", 50, 25, 25, position, 0, -1} {}

void Vampire::attack(std::shared_ptr<Enemy> enemy) {
    int hp = enemy->getHP();
    enemy->getStruckBy(std::make_shared<Vampire>(*this));
    if (hp != enemy->getHP()) {
        if (enemy->getRace() == "Dwarf") {
            setHP(getHP() - 5);
        }

        else {
            setHP(getHP() + 5);
        }
    }
}