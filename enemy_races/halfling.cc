#include "halfling.h"

Halfling::Halfling(std::pair<int, int> position) 
    : Enemy{"Halfling", "L", 100, 15, 20, position, true, randomGold(), true} {}

void Halfling::getStruckBy(std::shared_ptr<Shade> shade) {
    int miss = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (miss == 1) {
        int damage = calculateDamage(shade->getAtk(), getDef());
        int health = getHealth();
        health -= damage;
        setHealth(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(shade, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Drow> drow) {
    int miss = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (miss == 1) {
        int damage = calculateDamage(drow->getAtk(), getDef());
        int health = getHealth();
        health -= damage;
        setHealth(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(drow, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Vampire> vampire) {
    int miss = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (miss == 1) {
        int damage = calculateDamage(vampire->getAtk(), getDef());
        int health = getHealth();
        health -= damage;
        setHealth(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(vampire, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Troll> troll) {
    int miss = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (miss == 1) {
        int damage = calculateDamage(troll->getAtk(), getDef());
        int health = getHealth();
        health -= damage;
        setHealth(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(troll, std::make_shared<Halfling>(*this));
    }
}

void Halfling::getStruckBy(std::shared_ptr<Goblin> goblin) {
    int miss = rand() % 2;

    // Add in action messaged (like on page 8 of pdf)
    if (miss == 1) {
        int damage = calculateDamage(goblin->getAtk(), getDef());
        int health = getHealth();
        health -= damage;
        setHealth(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(goblin, std::make_shared<Halfling>(*this));
    }
}
