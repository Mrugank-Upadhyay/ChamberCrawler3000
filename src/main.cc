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

    std::string floorFile = "defaultFloor.txt";
    std::string testFile = "";

    std::shared_ptr<std::ifstream> inFile;

    // IS SEED AN INT?
    int seed;
    std::string args;
    for (int i = 0; i < argc; i++) {
        args = argv[i];
        
        // For now, assume its always cc3kfloor.txt, check piazza for reply to question
        if (args == "cc3kfloor.txt") {
            floorFile = args;
        }
        
        // replace with Seed (figure that out)
        else if (args == "XXXXXXX") {

        }

        else if (args.find("test") != std::string::npos) {
            testFile = args;
        }
    }

    /*
        SET SEED (if no seed, set srand((unsigned int)time(NULL)));
    */

    int floorHeight = 25;
    int floorWidth = 79;
    std::string playerClass;

    if (testFile != "") {
        inFile = std::make_shared<std::ifstream>(testFile);
        getline(*inFile, playerClass);
    }

    else {
        std::cin >> playerClass;
    }

    bool generate = (floorFile == "defaultFloor.txt") ? true : false;
    Display display{playerClass, floorFile, floorHeight, floorWidth, generate};


    /*


        Basically, if testfile was added, use commands from testfile to get caught up


    */


   // Figure out now, how to add NCURSES and also reset the game.
   std::string command;
   while(1) {
       std::cin >> command;
       display.applyCommand(command);
   }
}