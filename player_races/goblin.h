#ifndef _GOBLIN_
#define _GOBLIN_

#include "../player.h"

class Goblin: public Player {
  public:
    Goblin(std::pair<int, int> position);
    virtual void attack(std::shared_ptr<Enemy> enemy) override;
    virtual void getStruckBy(Orc * enemy) override;
    virtual void nextTurn() override;
};

#endif
