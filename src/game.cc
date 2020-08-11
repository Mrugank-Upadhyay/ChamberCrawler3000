#include "game.h"
#include "player.h"
#include "player_races/shade.h"
#include "player_races/drow.h"
#include "player_races/vampire.h"
#include "player_races/troll.h"
#include "player_races/goblin.h"
#include "floor.h"

#include <string>

Game::Game(std::string playerClass) : level{1} {
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
  currentFloor = std::make_shared<Floor>();
  currentFloor->getGrid().at(position)->setCharacter(player);
}
