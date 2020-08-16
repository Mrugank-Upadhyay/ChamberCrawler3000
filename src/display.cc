//#include <curses.h>
#include <stdlib.h>
#include <sstream>

#include "game.h"
#include "cell.h"
#include "floor.h"
#include "display.h"

#include "items/gold.h"
#include "items/potion.h"
#include <stdlib.h>

Display::Display(std::string playerClass, std::string file, int height, int width, bool generate)
  : height{height}, width{width} {
  game = std::make_shared<Game>(playerClass, file, height, width, generate);
  print();
  std::cout << "Action: Player character has spawned." << std::endl;
}

void Display::printFloor() {
  auto grid = game->getFloor()->getGrid();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      std::pair<int, int> position{x, y};
      if(grid.at(position)->getItem() != nullptr) {
        auto potion = std::dynamic_pointer_cast<Potion>(grid.at(position)->getItem());
        if(potion != nullptr) {
          if(visibleItems.count(potion->getRep()) == 0) {
            std::cout << "?";
            continue;
          }
        }
      }
      std::cout << grid.at(position)->getRep();
    }
    std::cout << std::endl;
  }
}

void Display::printInfo() {
    std::string output = "Race: " + game->getPlayer()->getRace() 
                       + " Gold: " + std::to_string(game->getPlayer()->getGold());
    std::cout << output << std::setw(width - 2 - output.length()) << "Floor " 
              << game->getLevel() << std::endl;
    std::cout << "Hp: "  << game->getPlayer()->getHP()     << std::endl;
    std::cout << "Atk: " << game->getPlayer()->getTmpATK() << std::endl;
    std::cout << "Def: " << game->getPlayer()->getTmpDEF() << std::endl;
}

void Display::print() {
    // call ncurses and do screen clear


    // SYSTEM CLEAR, MAY NEED TO DELETE IF NCURSES WORKS, OR THIS DOESNT ON STUDENT ENVIRONMENT
    // system("clear");

    
    printFloor();
    printInfo();
}

std::pair<int,int> operator+(std::pair<int,int> p1, std::pair<int,int> p2) {
  return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

void Display::movePlayer(std::pair<int, int> newpos) {
    auto player = game->getPlayer();
    auto dest = game->getFloor()->getGrid().at(newpos);
    std::shared_ptr<Player> nothing = nullptr;
      player->getCell()->setCharacter(nothing);
      player->setCell(dest.get());
      player->setPosition(newpos);
      player->getCell()->setCharacter(player);
}

bool Display::hasRestarted() {
  return restart;
}

void Display::applyCommand(std::string command) {

  std::map<std::string,std::pair<int,int>> directions;
  directions["no"] = std::make_pair(0,-1);
  directions["so"] = std::make_pair(0,1);
  directions["ea"] = std::make_pair(1,0);
  directions["we"] = std::make_pair(-1,0);
  directions["ne"] = directions["no"] + directions["ea"];
  directions["nw"] = directions["no"] + directions["we"];
  directions["se"] = directions["so"] + directions["ea"];
  directions["sw"] = directions["so"] + directions["we"];

  std::string message = "";

  if(game->getPlayer()->getHP() <= 0) {
    if(command != "r" && command != "q") {
      std::cout  << " PC has been slain. Only valid commands are (r)estart or (q)uit.\n" << std::endl;
      return;
    }
  }

  if (game->getLevel() == 6) {
    if(command != "r" && command != "q") {
      std::cout  << " PC has won. Only valid commands are (r)estart or (q)uit.\n" << std::endl;
      return;
    }
  }

  if (command == "r") {
    // add cout
    std::cout << "Restarting...\nClick Enter\n";
    restart = true;
    return;
  }
  // quit
  else if (command == "q") {
    std::cout << "Exiting...\n";
    exit(0);
  }

  // toggle freeze
  else if(command == "f") {
    if(Enemy::getStopped()) {
      Enemy::setStopped(false);
      message += " Enemies can move again.\n";
    }
    else {
      Enemy::setStopped(true);
      message += " Enemies now will not move after a turn.\n";
    }
  }

  else if (directions.count(command) == 1) {
    auto player = game->getPlayer();
    auto newpos = player->getPosition() + directions[command];
    auto dest = game->getFloor()->getGrid().at(newpos);
    std::string type = dest->getType();

    if (type == "Exit") {
      game->incrementLevel();
      if (game->getLevel() == 6) {
        std::cout << "PC has won " << std::endl;
        return;
      }

      message += "Going to next floor...\n";
      game->regenFloor();
    }

    else if((type != "Door") &&
       (type != "Passage") &&
       (type != "Floor")) { 
      std::cout << "Can't move there!\n" << std::endl;
    }
    else if (!dest->getOccupied()) {
      movePlayer(newpos);
       message += "PC moved to (" + std::to_string(dest->getPosition().first) + ", " + std::to_string(dest->getPosition().second) + ")\n";
       message += game->getFloor()->nextTurn();
    }

    else {
      if ((dest->getItem() != nullptr) && (dest->getItem()->getType() == "Gold")) {
        auto destGold = std::dynamic_pointer_cast<Gold>(dest->getItem());
        if (destGold->getCanPickUp()) {
          destGold->apply(player);
          dest->setItem(nullptr);
          movePlayer(newpos);
          message += "PC moved to (" + std::to_string(dest->getPosition().first) + ", " + std::to_string(dest->getPosition().second) + "). ";
          message += "PC picked up " + std::to_string(destGold->getAmount()) + " Gold\n";
          message += game->getFloor()->nextTurn();
        }
      }

      if ((dest->getItem() != nullptr) && (dest->getItem()->getType() == "Potion")) {
        std::cout << "Can't move there, a potion is in the way!" << std::endl;
      }

      if (dest->getEnemy() != nullptr) {
        std::cout << "Can't move there, an enemy is in the way!" << std::endl;
      }
    }
  }

  else if (command.substr(0, 2) == "u " && directions.count(command.substr(2)) == 1) {
    auto usePos = game->getPlayer()->getPosition() + directions[command.substr(2)];
    auto useCell = game->getFloor()->getGrid().at(usePos);
    if(useCell->getItem() != nullptr) {
      // See if the item is a potion or not.
      if (useCell->getItem()->getType() != "Gold") {
        auto potion = std::dynamic_pointer_cast<Potion>(useCell->getItem());
          potion->apply(game->getPlayer());
          message += "PC used a potion that changed Hp:Atk:Def by " + 
                      std::to_string(potion->getHP()) + ":" + 
                      std::to_string(potion->getATK()) + ":" +
                      std::to_string(potion->getDEF()) + "\n";
          visibleItems[potion->getRep()] = true;
          useCell->setItem(nullptr);
          message += game->getFloor()->nextTurn();
      }
      else {
        message += "Can't use that! There is no such thing as using gold in this game!";
      }
    }

    else {
      message += "Can't use that, enemies are not meant to be used!!";
    }
  }

  else if (command.substr(0, 2) == "a " && directions.count(command.substr(2)) == 1) {
    auto enemyPos = game->getPlayer()->getPosition() + directions[command.substr(2)];
    auto enemy = game->getFloor()->getGrid().at(enemyPos)->getEnemy();
    if(enemy != nullptr) {
      message += game->getPlayer()->attack(enemy);
      message += game->getFloor()->nextTurn();
    }
    else {
      message += " There is no enemy there to attack!";
    }
  }

  else {
    message = "Invalid Command!\n";
  }

  print();
  std::cout << message << std::endl;
  if(game->getPlayer()->getHP() <= 0) {std::cout  << " PC has been slain " << std::endl;}
}
