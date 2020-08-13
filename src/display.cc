//#include <curses.h>

#include "game.h"
#include "cell.h"
#include "floor.h"
#include "display.h"

#include "items/gold.h"

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

std::pair<int,int> operator+(std::pair<int,int> p1, std::pair<int,int> p2) {
  return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

void Display::applyCommand(std::string command) {
  std::cout << "Action ";
  // move commands
  std::map<std::string,std::pair<int,int>> directions;
  directions["no"] = std::make_pair(0,-1);
  directions["so"] = std::make_pair(0,1);
  directions["ea"] = std::make_pair(1,0);
  directions["we"] = std::make_pair(-1,0);
  directions["ne"] = directions["no"] + directions["ea"];
  directions["nw"] = directions["no"] + directions["we"];
  directions["se"] = directions["so"] + directions["ea"];
  directions["sw"] = directions["so"] + directions["we"];

  if(directions.count(command) == 1) {
    auto player = game->getPlayer();
    auto newPos = player->getPosition() + directions[command];
    auto destCell = game->getFloor()->getGrid().at(newPos);
    std::string type = destCell->getType();
    if(type == "Exit") {

    }
    if(destCell->getOccupied()) {
      if(destCell->getItem() != nullptr) {
        // Should work if downcasting returns nullptr on fail
        auto gold = std::dynamic_pointer_cast<Gold>(destCell->getItem());
        if(gold != nullptr) {
          // check if dragon is alive first.
          if(gold->getAmount() == 6) {
            std::cout << "Cannot move there! Dragon Hoard in the way!";
          }
          player->move(newPos);
          gold->apply(player);
          destCell->setItem(nullptr);
          destCell->setRep(".");
        }
        else {
          std::cout << "Cannot move there! An item is in the way!";
          return;
        }
      }
    }
  }

  std::cout << std::endl;
}
