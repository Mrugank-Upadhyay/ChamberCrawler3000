#ifndef _GAME_
#define _GAME_

#include <memory>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

class Player;
class Floor;
class Cell;

class Game {
    std::shared_ptr<Player> player;
    std::shared_ptr<Floor> currentFloor;
    int level = 1;
    std::shared_ptr<std::ifstream> infile;
    int height;
    int width;
    bool generate;

    std::string makeFloorString();

    std::vector<std::shared_ptr<Cell>> bfs();
    bool find(std::vector<std::shared_ptr<Cell>> & list, std::pair<int, int> pos);
    bool pairCmp(std::shared_ptr<Cell> c1, std::shared_ptr<Cell> c2);



    // std::map<std::pair<int, int>, std::shared_ptr<Cell>> bfs(
    //     std::map<std::pair<int, int>,std::shared_ptr<Cell>> & visited, 
    //     std::shared_ptr<Cell> cell);

  public:
    Game(std::string playerClass, std::string file, int height, int width, bool generate);

    std::shared_ptr<Player> getPlayer();
    void genPlayer(std::shared_ptr<Player> player);

    int getLevel() const;
    void incrementLevel();
    void resetLevel();

    std::shared_ptr<Floor> getFloor();
    // check potion reveal
    void regenFloor();

    void tick();
};

#endif
