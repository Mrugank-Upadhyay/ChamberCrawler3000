#include "player.h"
#include "player_races/shade.h"
#include "player_races/drow.h"
#include "player_races/vampire.h"
#include "player_races/troll.h"
#include "player_races/goblin.h"
#include "floor.h"
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
  infile = std::make_shared<std::ifstream>(file);

  currentFloor = std::make_shared<Floor>(makeFloorString(), height, width, generate);
  currentFloor->getGrid().at(position)->setCharacter(player);
}

std::string & Game::makeFloorString() {
  std::string line;
  std::string output = "";
  for (int i = 0; i < height; i++) {
    getline(*infile, line);
    output.append(line + "\n");
  }

  return output;
}

// When generating player, create queue of cells to check around exit. Once done perform not intersect floorCells with queue
// From there you are given a vector of potential places for player to spawn.