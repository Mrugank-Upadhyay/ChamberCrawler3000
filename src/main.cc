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


int main(int argc, char * argv[]) {

    std::string floorFile = "./src/defaultFloor.txt";
    std::string testFile = "";

    std::shared_ptr<std::ifstream> inFile;

    int seed = -1;
    std::string args;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-f") {
            args = argv[i + 1];
            floorFile = args;
            i += 2;
        }

        else if (argv[i] == "-s") {
            args = argv[i + 1];
            seed = std::stoi(args);
            i += 2;
        }
        else if (argv[i] == "-t"){
            args = argv[i + 1];
            testFile = args;
            i += 2;
        }
    }

    /*
        SET SEED (if no seed, set srand((unsigned int)time(NULL)));
    */

   if (seed == -1) {
        srand((unsigned int)time(NULL));
   }

   else {
       srand((unsigned int)seed);
   }

     int floorHeight = 25;
     int floorWidth = 79;
     std::string playerClass;

    // Valid place to put while loop to reset everything?
    /*

        while {

            Stuff Below
        }

        if display.applycommand("r"),
        then its reset bool gets set,
        then we break out of the below loop 

    */

    if (testFile != "") {
        inFile = std::make_shared<std::ifstream>(testFile);
        getline(*inFile, playerClass);
    }

    else {
        getline(std::cin, playerClass);
    }

    bool generate = (floorFile == "./src/defaultFloor.txt") ? true : false;
    std::unique_ptr<Display> display = std::make_unique<Display>(playerClass, floorFile, floorHeight, floorWidth, generate);

   std::string command;

   if (testFile != "") {
       while(1) {
           getline(*inFile, command);
           display->applyCommand(command);
       }
   }

    while (1) {
        display = std::make_unique<Display>(playerClass, floorFile, floorHeight, floorWidth, generate);
        while(1) {
            getline(std::cin, command);
            display->applyCommand(command);
            if (display->hasRestarted()) {
                break;
            }
        }
    }
   
}
