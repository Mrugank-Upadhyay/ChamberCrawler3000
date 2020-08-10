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

//void printInfo(std::shared_ptr<Character> character) {
    //cout << character->getHP() << " "
         //<< character->getATK() << " "
         //<< character->getDEF() << " "
         //<< character->getRace() << " "
         //<< character->getRep() << " "
         //<< character->getPosition().first << "," << character->getPosition().second << " ";
    //if (typeid(character) == typeid(Player)) {
        //std::shared_ptr<Player> characterP = dynamic_pointer_cast<Player>(character);
        //cout << characterP->getGold() << " "
             //<< characterP->getMaxHP() << " "
             //<< characterP->getTmpATK() << " "
             //<< characterP->getTmpDEF() << " "
             //<< boolalpha << characterP->isTurnFinished() << " " << endl;
    //}

    //else {
        //std::shared_ptr<Enemy> characterE = dynamic_pointer_cast<Enemy>(character);
        ////cout << boolalpha << characterE->getHostile() << " " << endl;
             ////<< characterE->getGold() << " " << endl;
    //}   
//}

int main() {
    auto human = std::make_shared<Human>(std::pair<int, int>(0,0)); // Enemy
    auto troll = std::make_shared<Troll>(std::pair<int, int>(1,4)); // Player
    auto bapotion = std::make_shared<BAPotion>("?", std::pair<int,int>(9,8)); // Potion
    auto goldpile = std::make_shared<Gold>(std::make_pair<int,int>(1,1),6); // Gold

    cout << human->info() << endl;
    cout << troll->info() << endl;
    cout << bapotion->info() << endl;
    cout << goldpile->info() << endl;
    
    //printInfo(human);
    //printInfo(troll);
    //human->attack(troll);
    //troll->attack(human);
    //printInfo(human);
    //printInfo(troll);
}
