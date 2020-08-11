#ifndef _GAME_
#define _GAME_

#include <memory>

class Player;
class Floor;

class Game {
    std::shared_ptr<Player> player;
    std::shared_ptr<Floor> currentFloor;
    int level = 1;
  public:
    Game(std::string playerClass);

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
