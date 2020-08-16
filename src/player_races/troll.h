#ifndef _TROLL_
#define _TROLL_

#include "../player.h"

class Troll: public Player {
  public:
    Troll(std::pair<int, int> position);
    virtual std::string attack(std::shared_ptr<Enemy> enemy) override;
    virtual void nextTurn() override;
};

#endif
