#include "player.h"
#include "potion.h"

Potion::Potion(std::string type, std::string rep, std::pair<int, int> position)
    : Item{type, rep, position} {}

int Potion::getHP() {
    return hp;
}

int Potion::getATK() {
    return atk;
}

int Potion::getDEF() {
    return def;
}



void Potion::apply(Player p) {
    p->applyItem(std::make_shared<Potion>(*this));
}

std::string Potion::printInfo() {
    std::string message;

    if (health != 0) {
        message = std::to_string(health);
    }

    else if (atk != 0) {
        message = std::to_string(atk);
    }

    else if (def != 0) {
        message = std::to_string(def);
    } 
}