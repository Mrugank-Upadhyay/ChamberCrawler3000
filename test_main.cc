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

#include "cell.h"
#include "display.h"
#include "game.h"
#include "floor.h"
#include <memory>

#include <iostream>
using namespace std;

int main() {
    // auto game = std::make_shared<Game>("Shade", "./src/defaultFloor.txt", 25, 79, true);
    srand((unsigned int) time(NULL));
    //srand(100);
    auto display = std::make_shared<Display>("Shade", "./src/defaultFloor.txt", 25, 79, true);
    display->applyCommand("no");
    // auto game = display->getGame();
    // cout << endl;
    // int count = 0;
    // for (auto cell : game->getFloor()->getFloorCell()) {
    //     cout << cell->getRep();
    //     count++;
    //     if (count % 79 == 0) {
    //         cout << endl;
    //     }
    // }
    //display->print();
}
