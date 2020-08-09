#include "halfling.h"

Halfling::Halfling(std::pair<int, int> position) 
    : Enemy{"Halfling", "L", 100, 15, 20, position, true, 0, true} {
        setGold(randomGold());
}


void Halfling::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(this);
}

void Halfling::getStruckBy(Shade * shade) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(shade->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(shade);
    }
}

void Halfling::getStruckBy(Drow * drow) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(drow->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(drow);
    }
}

void Halfling::getStruckBy(Vampire * vampire) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(vampire->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(vampire);
    }
}

void Halfling::getStruckBy(Troll * troll) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(troll->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(troll);
    }
}

void Halfling::getStruckBy(Goblin * goblin) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(goblin->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(goblin);
    }
}

void Halfling::nextTurn() {}
