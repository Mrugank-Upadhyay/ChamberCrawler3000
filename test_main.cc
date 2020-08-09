#include "./player_races/shade.h"
#include "./player_races/drow.h"
#include "./player_races/vampire.h"
#include "./player_races/troll.h"
#include "./player_races/goblin.h"

#include "./enemy_races/human.h"
#include "./enemy_races/dwarf.h"
#include "./enemy_races/elf.h"
#include "./enemy_races/orc.h"
#include "./enemy_races/merchant.h"
#include "./enemy_races/dragon.h"
#include "./enemy_races/halfling.h"

#include "./items/gold.h"
#include "./items/potion.h"
#include "./items/potion_types/RHpotion.h"
#include "./items/potion_types/BApotion.h"
#include "./items/potion_types/BDpotion.h"
#include "./items/potion_types/PHpotion.h"
#include "./items/potion_types/WApotion.h"
#include "./items/potion_types/WDpotion.h"

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