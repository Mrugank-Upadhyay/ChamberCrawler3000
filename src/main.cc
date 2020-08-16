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
        args = argv[i];
        if (args == "-f") {
            args = argv[i + 1];
            floorFile = args;
            i += 2;

            std::cout << "FILE INPUT" << std::endl;
            std::cout << floorFile << std::endl;
            std::cout << args << std::endl;
        }

        else if (args == "-s") {
            args = argv[i + 1];
            seed = std::stoi(args);
            i += 2;
        }
        else if (args == "-t"){
            args = argv[i + 1];
            testFile = args;
            i += 2;
        }
    }

   if (seed == -1) {
        srand((unsigned int)time(NULL));
   }

   else {
       srand((unsigned int)seed);
   }

   while(1) {
        int floorHeight = 25;
        int floorWidth = 79;
        std::string playerClass;

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
                if (std::cin.fail()) {
                    break;
                }
                display->applyCommand(command);
            }
        }

        while(1) {
            getline(std::cin, command);
            display->applyCommand(command);
            if (display->hasRestarted()) {
                break;
            }
        }
    } 
}
