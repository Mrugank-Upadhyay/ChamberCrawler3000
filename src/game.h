#ifndef _GAME_
#define _GAME_

#include <memory>
#include <fstream>
#include <iostream>

class Player;
class Floor;

class Game {
    std::shared_ptr<Player> player;
    std::shared_ptr<Floor> currentFloor;
    int level = 1;
    std::shared_ptr<std::ifstream> infile;
    int height;
    int width;
    bool generate;

    std::string & makeFloorString();

  public:
    Game(std::string playerClass, std::string file, int height, int width, bool generate);

    std::shared_ptr<Player> getPlayer();
    void genPlayer(std::shared_ptr<Player> player);

    int getLevel() const;
    void incrementLevel();
    void resetLevel();

    std::shared_ptr<Floor> getFloor();
    void regenFloor();

    void tick();
};

#endif
