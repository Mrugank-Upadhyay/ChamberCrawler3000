#include "halfling.h"

Halfling::Halfling(std::pair<int, int> position) 
    : Enemy{"Halfling", "L", 100, 15, 20, position, true, randomGold(), true} {}


void Halfling::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(std::make_shared<Halfling>(this));
}

void Halfling::getStruckBy(std::shared_ptr<Shade> shade) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(shade->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(shade, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Drow> drow) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(drow->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(drow, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Vampire> vampire) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(vampire->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(vampire, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Troll> troll) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(troll->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(troll, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Goblin> goblin) {
    int hit = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        int damage = calculateDamage(goblin->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(goblin, std::make_shared<Halfling>(*this));
    }
}
