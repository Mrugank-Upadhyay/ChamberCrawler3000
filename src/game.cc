#include "player.h"
#include "player_races/shade.h"
#include "player_races/drow.h"
#include "player_races/vampire.h"
#include "player_races/troll.h"
#include "player_races/goblin.h"
#include "floor.h"
#include "cell.h"
#include "game.h"

#include <string>

Game::Game(std::string playerClass, std::string file, int height, int width, bool generate) 
  : level{1}, height{height}, width{width}, generate{generate} {

  auto position = std::make_pair<int, int>(0,0);
  if(playerClass == "Drow") {
    player = std::dynamic_pointer_cast<Player>(std::make_shared<Drow>(position));
  }
  else if(playerClass == "Vampire") {
    player = std::dynamic_pointer_cast<Player>(std::make_shared<Vampire>(position));
  }
  else if(playerClass == "Troll") {
    player = std::dynamic_pointer_cast<Player>(std::make_shared<Troll>(position));
  }
  else if(playerClass == "Goblin") {
    player = std::dynamic_pointer_cast<Player>(std::make_shared<Goblin>(position));
  }
  else {
    player = std::dynamic_pointer_cast<Player>(std::make_shared<Shade>(position));
  }
  
  // make sure to check arg in main for file input, if none, use default file
  // when reset game (call back the string, make new ifstream)
  infile = std::make_shared<std::ifstream>(file);
  currentFloor = std::make_shared<Floor>(makeFloorString(), height, width, generate);
  std::cout << "success" << std::endl;
  genPlayer(player);
}

std::string Game::makeFloorString() {
  std::string line;
  std::string output = "";
  for (int i = 0; i < height; i++) {
    getline(*infile, line);
    output.append(line);
  }

  return output;
}

bool Game::pairCmp(std::shared_ptr<Cell> c1, std::shared_ptr<Cell> c2) {
  return c1->getPosition() < c2->getPosition();
}


void Game::genPlayer(std::shared_ptr<Player> player) {
  auto bfsChamber = bfs();

  // std::cout << "success" << std::endl;

  //
  // bfs is now returning a map!!!!!!
  //

  std::map<std::pair<int, int>, std::shared_ptr<Cell>> floorMap;
  for (auto cell : currentFloor->getFloorCell()) {
    floorMap[cell->getPosition()] = cell;
  }
  
  std::map<std::pair<int, int>, std::shared_ptr<Cell>> availableSpawn;
  auto it = std::set_difference(floorMap.begin(), floorMap.end(), bfsChamber.begin(), bfsChamber.end(), availableSpawn.begin());
  for (auto elem : availableSpawn) {
    std::cout << elem.second->info() << std::endl;
  }

  // std::sort(bfsChamber.begin(), bfsChamber.end(), pairCmp);
  // std::sort(currentFloor->getFloorCell().begin(), currentFloor->getFloorCell().end(), pairCmp);
  // std::vector<std::shared_ptr<Cell>> availableSpawn;
  // auto it = std::set_difference(currentFloor->getFloorCell().begin(), currentFloor->getFloorCell().end(), bfsChamber.begin(), bfsChamber.end(), availableSpawn.begin());
  // availableSpawn.resize(it - availableSpawn.begin());

  int length = availableSpawn.size();

  while (1) {
    int random = rand() % length;
    auto it = availableSpawn.begin();
    std::shared_ptr<Cell> cell;
    for (int i = 0; i < length; i++) {
      it++;
    }

    cell = it->second;

    if (!cell->getOccupied()) {
      player->setPosition(cell->getPosition());
      player->setCell(cell);
      cell->setCharacter(player);
      break;
    }
  }
}

std::shared_ptr<Player> Game::getPlayer() {
  return player;
}

int Game::getLevel() const {
  return level;
}

void Game::incrementLevel() {
  level++;
}

void Game::resetLevel() {
  level = 1;
}

std::shared_ptr<Floor> Game::getFloor() {
  return currentFloor;
}

bool Game::hasWon() {
  return victory;
}

void Game::setWon(bool win) {
  victory = win;
}

std::map<std::pair<int, int>, std::shared_ptr<Cell>> Game::bfs() {

  std::map<std::pair<int, int>, std::shared_ptr<Cell>> queue;

  for (auto obs : currentFloor->getExit()->getObservers()) {
    auto cell = std::dynamic_pointer_cast<Cell>(obs);
    queue[cell->getPosition()] = cell;
  }

  for (auto cell : queue) {
    for (auto neighbour : (cell.second)->getObservers()) {
      auto neighbourCell = std::dynamic_pointer_cast<Cell>(neighbour);
      if ((neighbourCell->getType() == "Door") || (neighbourCell->getType() == "Passage")) {
        continue;
      }

      else if (queue.find(neighbourCell->getPosition()) == queue.end()) {
        queue[neighbourCell->getPosition()] = neighbourCell;
      }
    }
  }

  return queue;
}


void Game::regenFloor() {
  currentFloor = std::make_shared<Floor>(makeFloorString(), height, width, generate);
  genPlayer(player);
  player->setTmpATK(player->getATK());
  player->setTmpDEF(player->getDEF());

}

bool Game::tick() {
  if (player->getHP() == 0) {
    return false;
  }
  currentFloor->nextTurn();
  return true;
}
