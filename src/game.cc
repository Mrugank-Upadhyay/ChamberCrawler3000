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

  // maybe add the player afterwards when we do the dfs on a randomly generated floor cell
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
    output.append(line + "\n");
  }

  return output;
}

bool Game::pairCmp(std::shared_ptr<Cell> c1, std::shared_ptr<Cell> c2) {
  return c1->getPosition() < c2->getPosition();
}


void Game::genPlayer(std::shared_ptr<Player> player) {
  auto bfsChamber = bfs();
  std::sort(bfsChamber.begin(), bfsChamber.end(), pairCmp);
  std::sort(currentFloor->getFloorCell().begin(), currentFloor->getFloorCell().end(), pairCmp);
  std::vector<std::shared_ptr<Cell>> availableSpawn;
  auto it = std::set_difference(currentFloor->getFloorCell().begin(), currentFloor->getFloorCell().end(), bfsChamber.begin(), bfsChamber.end(), availableSpawn.begin());
  availableSpawn.resize(it - availableSpawn.begin());

  int length = availableSpawn.size();

  while (1) {
    int random = rand() % length;
    auto cell = availableSpawn[random];

    if (!cell->getOccupied()) {
      player->setPosition(cell->getPosition());
      player->setCell(cell);
      cell->setCharacter(player);
      break;
    }
  }
}

bool Game::find(std::vector<std::shared_ptr<Cell>> & list, std::pair<int, int> pos) {
   for(auto cell : list) {
    if (cell->getPosition() == pos) {
      return true;
    }
  }

  return false;
}

std::vector<std::shared_ptr<Cell>> Game::bfs() {
  std::vector<std::shared_ptr<Cell>> queue;

  queue.insert(queue.end(), currentFloor->getExit()->getObservers().begin(), currentFloor->getExit()->getObservers().end());

  for (auto cell : queue) {
    for (auto neighbour : cell->getObservers()) {
      auto neighbourCell = std::dynamic_pointer_cast<Cell>(neighbour);
      if (!find(queue, neighbourCell->getPosition())) {
        queue.push_back(neighbourCell);
      }
    }
  }

  return queue;
}


// std::map<std::pair<int, int>, std::shared_ptr<Cell>> Game::bfs(
//     std::map<std::pair<int, int>, std::shared_ptr<Cell>> & visited, 
//     std::shared_ptr<Cell> cell) {
//   auto observers = cell->getObservers();
//   visited[cell->getPosition()] = cell;
//   for(auto obs: observers) {
//     auto obsCell = std::dynamic_pointer_cast<Cell>(obs);
//     if(visited.count(obsCell->getPosition()) == 0) {
//       if(!obsCell->getOccupied() && obsCell->getType() == "Floor") {
//         bfs(visited, obsCell);
//       }
//     }
//   }
//   return visited;
// }
