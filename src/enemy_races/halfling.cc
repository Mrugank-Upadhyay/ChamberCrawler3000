#include "halfling.h"
#include "../player_races/shade.h"
#include "../player_races/drow.h"
#include "../player_races/vampire.h"
#include "../player_races/troll.h"
#include "../player_races/goblin.h"

Halfling::Halfling(std::pair<int, int> position) 
    : Enemy{"Halfling", "L", 100, 15, 20, position, true, 0, true} {
        setGold(randomGold());
}


std::string Halfling::attack(std::shared_ptr<Player> player) {
    return player->getStruckBy(this);
}

std::string Halfling::getStruckBy(Shade * shade) {
    int hit = rand() % 2;

    int damage = 0;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        damage = calculateDamage(shade->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(shade);
    }

    return "PC Deals " + std::to_string(damage) + " to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
}

std::string Halfling::getStruckBy(Drow * drow) {
    int hit = rand() % 2;
    int damage = 0;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        damage = calculateDamage(drow->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(drow);
    }

    return "PC Deals " + std::to_string(damage) + " to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
}

std::string Halfling::getStruckBy(Vampire * vampire) {
    int hit = rand() % 2;
    int damage = 0;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        damage = calculateDamage(vampire->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(vampire);
    }

    return "PC Deals " + std::to_string(damage) + " to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
}

std::string Halfling::getStruckBy(Troll * troll) {
    int hit = rand() % 2;
    int damage = 0;

    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        damage = calculateDamage(troll->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(troll);
    }

    return "PC Deals " + std::to_string(damage) + " to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
}

std::string Halfling::getStruckBy(Goblin * goblin) {
    int hit = rand() % 2;
    int damage = 0;
    // Add in action messaged (like on page 8 of pdf)
    if (hit == 1) {
        damage = calculateDamage(goblin->getATK(), getDEF());
        int health = getHP();
        health -= damage;
        setHP(health);
        // Will this need to notify cell when health == 0?
        // if so, how?
        transferGold(goblin);
    }

    return "PC Deals " + std::to_string(damage) + " to " + getRep() + " (" + std::to_string(getHP()) + " HP). ";
}

void Halfling::nextTurn() {}
