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

template<class A,class B>
std::map<A,B> setDiff(std::map<A,B> & set1, std::map<A,B> & set2) {
  std::map<A,B> newMap;
  for(auto elem: set1) {
    if(set2.count(elem.first) == 0) {
      newMap[elem.first] = elem.second;
    }
  }
  return newMap;
}

void Game::genPlayer(std::shared_ptr<Player> player) {
  auto bfsChamber = bfs();

  std::map<std::pair<int, int>, std::shared_ptr<Cell>> floorMap;
  for (auto cell : currentFloor->getFloorCell()) {
    floorMap[cell->getPosition()] = cell;
  }
  
  std::map<std::pair<int, int>, std::shared_ptr<Cell>> availableSpawn = setDiff(floorMap, bfsChamber);

  int length = availableSpawn.size();

  while (1) {
    int random = rand() % length;
    auto it = availableSpawn.begin();
    std::shared_ptr<Cell> cell;
    for (int i = 0; i < random; i++) {
      it++;
    }
    cell = it->second;

    if ((!cell->getOccupied()) && ((cell->getType() != "Door") && (cell->getType() != "Passage"))) {
      player->setPosition(cell->getPosition());
      player->setCell(cell.get());
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




bool Game::find(std::vector<std::shared_ptr<Cell>> list, std::pair<int, int> pos) {
  for (auto cell : list) {
    if (cell->getPosition() == pos) {
      return true;
    }
  }

  return false;
}


std::map<std::pair<int, int>, std::shared_ptr<Cell>> Game::bfs() {

  std::map<std::pair<int, int>, std::shared_ptr<Cell>> returnQueue;
  std::vector<std::shared_ptr<Cell>> queue;
  queue.push_back(currentFloor->getExit());

  for (int i = 0; i < queue.size(); i++) {
      auto cell = queue[i];
    for (auto neighbour : cell->getObservers()) {
      auto neighbourCell = dynamic_cast<Cell *>(neighbour);
      // std::cout << "obs(" << neighbourCell->getPosition().first << "," << neighbourCell->getPosition().second <<") ";
      if (neighbourCell->getType() == "Door") {
        continue;
      }

      else if (!find(queue, neighbourCell->getPosition())) {
        // possible point of failure. used Cell * neighbour's position to get sharedptr from grid for that position
        auto gridCell = currentFloor->getGrid()[neighbourCell->getPosition()];
        // std::cout << "grid(" << gridCell->getPosition().first << "," << gridCell->getPosition().second <<") ";

        // std::cout << "queue len: " << queue.size() << std::endl;
        queue.push_back(gridCell);
      }
    }
  }

  for (auto cell : queue) {
    returnQueue[cell->getPosition()] = cell;
  }

  return returnQueue;
}


void Game::regenFloor() {

  for (auto cell : currentFloor->getGrid()) {
    cell.second->getObservers().clear();
  }
  currentFloor->getGrid().clear();
  currentFloor->getFloorCell().clear();
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
