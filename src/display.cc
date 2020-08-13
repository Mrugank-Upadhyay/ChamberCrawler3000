#include "game.h"
#include "cell.h"
#include "floor.h"
//#include <curses.h>
#include "display.h"

Display::Display(std::string playerClass, std::string file, int height, int width, bool generate)
    : height{height}, width{width} {
    game = std::make_shared<Game>(playerClass, file, height, width, generate);
}

void Display::printFloor() {
    auto grid = game->getFloor()->getGrid();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[std::pair<int, int>(x, y)]->getRep();
        }
        std::cout << std::endl;
    }
}

void Display::printInfo() {
    std::string output = "Race: " + game->getPlayer()->getRace() 
                       + " Gold: " + std::to_string(game->getPlayer()->getGold());
    std::cout << output << std::setw(width - output.length()) << "Floor " << game->getLevel() << std::endl;
}

void Display::print() {
    // call ncurses and do screen clear
    printFloor();
    printInfo();
}

void Display::applyCommand(std::string command) {
    
}