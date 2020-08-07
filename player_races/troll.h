#ifndef _TROLL_
#define _TROLL_

#include "../player.h"

class Troll: public Player {
  public:
    Troll(std::pair<int, int> position);
    void nextTurn() override;
    void attack(std::shared_ptr<Enemy> enemy) override;
};

#endif
