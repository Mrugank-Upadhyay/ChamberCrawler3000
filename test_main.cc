#include "headerfiles.h"
#include <iostream>
using namespace std;

void printInfo(std::shared_ptr<Character> character) {
    cout << character->getHP() << " "
         << character->getATK() << " "
         << character->getDEF() << " "
         << character->getRace() << " "
         << character->getRep() << " ";
    if (typeid(character) == typeid(Player)) {
        std::shared_ptr<Player> characterP = dynamic_pointer_cast<Player>(character);
        cout << characterP->getGold();
    }
}

int main() {
    std::shared_ptr<Human> human = std::make_shared<Human>(std::pair<int, int>(0,0));
    cout << human->getHP();
}