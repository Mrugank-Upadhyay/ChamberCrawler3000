//#include <curses.h>
#include <stdlib.h>
#include <sstream>

#include "game.h"
#include "cell.h"
#include "floor.h"
#include "display.h"

#include "items/gold.h"
#include "items/potion.h"

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
      // std::cout << "works till here" << std::endl;
      // std::cout << "works after turn" << std::endl;
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


  // if player slain only allow restart or quit
  if(game->getPlayer()->getHP() <= 0) {
    if(command != "r" && command != "q") {
      std::cout  << " PC has been slain. Only valid commands are (r)estart or (q)uit."
                << std::endl;
      return;
    }
  }

  if (command == "r") {
    // regen game
    // game->regenFloor();
    // action << std::endl;
  }
  // quit
  else if(command == "q") {
    // action << " Exiting the Game..." << std::endl;
    exit(0);
  }

  if (directions.count(command) == 1) {
    auto player = game->getPlayer();
    auto newpos = player->getPosition() + directions[command];
    auto dest = game->getFloor()->getGrid().at(newpos);
    std::string type = dest->getType();

    if (type == "Exit") {
      // action << " Going to the next floor..." << std::endl;
      game->incrementLevel();
      // if player has won only allow restart or quit
      std::cout << "LEVEL: " << game->getLevel();
      if (game->getLevel() == 6) {
        std::cout << "PC WON!!!!" << std::endl;
        return;
      }
      game->regenFloor();
      player->setTmpATK(player->getATK());
      player->setTmpDEF(player->getDEF());
      return;
    }

    else if((type != "Door") &&
       (type != "Passage") &&
       (type != "Floor")) { 
      // action << " Cannot move there!" << std::endl;
      std::cout << "CAN'T MOVE THERE" << std::endl;
    }
    else if (!dest->getOccupied()) {
      // std::cout << "I'm FREE!" << std::endl;
      movePlayer(newpos);
    }

    else {

      // std::cout << "INSIDE ELSE" << std::endl;
      if ((dest->getItem() != nullptr) && (dest->getItem()->getType() == "Gold")) {
        auto destGold = std::dynamic_pointer_cast<Gold>(dest->getItem());
        if (destGold->getCanPickUp()) {
          destGold->apply(player);
          dest->setItem(nullptr);
          movePlayer(newpos);
        }
      }

      if ((dest->getItem() != nullptr) && (dest->getItem()->getType() == "Potion")) {
        std::cout << "CAN'T MOVE THERE! POTION IN THE WAY" << std::endl;
      }

      if (dest->getEnemy() != nullptr) {
        std::cout << "CAN'T MOVE THERE! ENEMY IS THERE!" << std::endl;
      }
    }
  }

  else if (command.substr(0, 2) == "u " && directions.count(command.substr(2)) == 1) {
    std::cout << "I witness this command" << std::endl;
    auto usePos = game->getPlayer()->getPosition() + directions[command.substr(2)];
    auto useCell = game->getFloor()->getGrid().at(usePos);
    if(useCell->getItem() != nullptr) {
      // See if the item is a potion or not.
      if (useCell->getItem()->getType() == "Potion") {
        auto potion = std::dynamic_pointer_cast<Potion>(useCell->getItem());
        if(potion != nullptr) {
          potion->apply(game->getPlayer());
          visibleItems[potion->getType()] = false;
          useCell->setItem(nullptr);
        }
      }
    }
  }

  else if (command.substr(0, 2) == "a " && directions.count(command.substr(2)) == 1) {
    auto enemyPos = game->getPlayer()->getPosition() + directions[command.substr(2)];
    auto enemy = game->getFloor()->getGrid().at(enemyPos)->getEnemy();
    if(enemy != nullptr) {
      game->getPlayer()->attack(enemy);
      //game->getFloor()->nextTurn();
    }
    else {
      std::cout << " There is no enemy there to attack!";
    }
  }

  game->getFloor()->nextTurn();

  print();

  // std::stringstream action{""};
  // action << "Action:";

  // // if player slain only allow restart or quit
  // if(game->getPlayer()->getHP() <= 0) {
  //   if(command != "r" && command != "q") {
  //     action << " PC has been slain. Only valid commands are (r)estart or (q)uit."
  //               << std::endl;
  //     return;
  //   }
  // }

  // // if player has won only allow restart or quit
  // if(game->hasWon()) {
  //   if(command != "r" && command != "q") {
  //     action << " PC has won. Only valid commands are (r)estart or (q)uit."
  //               << std::endl;
  //     return;
  //   }
  // }

  // // toggle freeze
  // if(command == "f") {
  //   if(Enemy::getStopped()) {
  //     Enemy::setStopped(false);
  //     action << " Enemies can move again.";
  //   }
  //   else {
  //     Enemy::setStopped(true);
  //     action << " Enemies now will not move after a turn.";
  //   }
  //   action << std::endl;
  // }
  // // restart
  // else if(command == "r") {
  //   // regen game
  //   action << std::endl;
  // }
  // // quit
  // else if(command == "q") {
  //   action << " Exiting the Game..." << std::endl;
  //   exit(0);
  // }

  // // directions
  // std::map<std::string,std::pair<int,int>> directions;
  // directions["no"] = std::make_pair(0,-1);
  // directions["so"] = std::make_pair(0,1);
  // directions["ea"] = std::make_pair(1,0);
  // directions["we"] = std::make_pair(-1,0);
  // directions["ne"] = directions["no"] + directions["ea"];
  // directions["nw"] = directions["no"] + directions["we"];
  // directions["se"] = directions["so"] + directions["ea"];
  // directions["sw"] = directions["so"] + directions["we"];

  // // move command
  // if(directions.count(command) == 1) {
  //   auto player = game->getPlayer();
  //   auto newPos = player->getPosition() + directions[command];
  //   auto destCell = game->getFloor()->getGrid().at(newPos);
  //   std::string type = destCell->getType();

  //   action << " New pos(" << newPos.first << "," << newPos.second << ").";
  //   action << destCell->info();

  //   if(type == "Exit") {
  //     action << " Going to the next floor..." << std::endl;
  //     game->regenFloor();
  //     player->setTmpATK(player->getATK());
  //     player->setTmpDEF(player->getDEF());
  //     print();
  //     return;
  //   }
  //   else if((type != "Door") &&
  //      (type != "Passage") &&
  //      (type != "Floor")) { 
  //     action << " Cannot move there!" << std::endl;
  //     return;
  //   }

  //   else if(destCell->getOccupied()) {
  //     action << std::boolalpha << destCell->getOccupied();
  //     if(destCell->getItem() != nullptr) {
  //       auto gold = std::dynamic_pointer_cast<Gold>(destCell->getItem());
  //       if(gold != nullptr) {
  //         if(!gold->getCanPickUp()) {
  //           action 
  //             << " Can't go there! It seems that the gold over there cannot be picked up."
  //             << std::endl;
  //           return;
  //         }
  //         else {
  //           player->move(newPos);
  //           gold->apply(player);
  //           destCell->setItem(nullptr);
  //           destCell->setRep(".");
  //           action << " PC picked up " << gold->getAmount() << " gold.";
  //           game->getFloor()->nextTurn();
  //         }
  //       }
  //       else {
  //         action << " Cannot move there! An item is in the way!";
  //       }
  //     }
  //     else if(destCell->getEnemy() != nullptr) {
  //       action << " Cannot move there! An enemy is positioned there!";
  //     }
  //   }
  //   else {
  //     player->move(newPos);
  //     action << " player moved " + command + ".";
  //     //game->getFloor()->nextTurn();
  //   }
  // }

  // // use command
  // else if(command.substr(0,2) == "u " && directions.count(command.substr(2)) == 1) {
  //   auto usePos = game->getPlayer()->getPosition() + directions[command.substr(2)];
  //   auto useCell = game->getFloor()->getGrid().at(usePos);
  //   if(useCell->getItem() != nullptr) {
  //     // See if the item is a potion or not.
  //     auto potion = std::dynamic_pointer_cast<Potion>(useCell->getItem());

  //     if(potion != nullptr) {
  //       potion->apply(game->getPlayer());
  //       action << " PC uses " << potion->getType() << ".";
  //       visibleItems[potion->getType()] = false;
  //       //action << " PC used a potion that has increased your hp:atk:def by "
  //                 //<< potion->getHP() << ":"
  //                 //<< potion->getATK() << ":"
  //                 //<< potion->getDEF() << ".";
  //       game->getFloor()->nextTurn();
  //     }
  //     else {
  //       action << " PC cannot use that item!";
  //     }

  //   }
  //   else {
  //     action << " There is no item there to use!";
  //   }
  // }

  // // attack command
  // else if(command.substr(0,2) == "a " && directions.count(command.substr(2)) == 1) {
  //   auto enemyPos = game->getPlayer()->getPosition() + directions[command.substr(2)];
  //   auto enemy = game->getFloor()->getGrid().at(enemyPos)->getEnemy();
  //   if(enemy != nullptr) {
  //     game->getPlayer()->attack(enemy);
  //     //game->getFloor()->nextTurn();
  //   }
  //   else {
  //     action << " There is no enemy there to attack!";
  //   }
  // }

  // action << std::endl;

  // print();
  // std::cout << action.str();
}
