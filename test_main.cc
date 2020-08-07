#include "headerfiles.h"
#include <iostream>
using namespace std;

void printInfo(std::shared_ptr<Character> character) {
    cout << character->getHP() << " "
         << character->getATK() << " "
         << character->getDEF() << " "
         << character->getRace() << " "
         << character->getRep() << " "
         << character->getPosition().first << "," << character->getPosition().second << " ";
    if (typeid(character) == typeid(Player)) {
        std::shared_ptr<Player> characterP = dynamic_pointer_cast<Player>(character);
        cout << characterP->getGold() << " "
             << characterP->getMaxHP() << " "
             << characterP->getTmpATK() << " "
             << characterP->getTmpDEF() << " "
             << boolalpha << characterP->isTurnFinished() << " ";
    }

    else {
        std::shared_ptr<Enemy> characterE = dynamic_pointer_cast<Enemy>(character);
        cout << boolalpha << characterE->getHostile() << " "
             << characterE->getGold() << " ";
    }   
}

int main() {
    std::shared_ptr<Human> human = std::make_shared<Human>(std::pair<int, int>(0,0));
    printInfo(human);
}