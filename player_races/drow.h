#ifndef _DROW_
#define _DROW_

#include "../player.h"

class Drow: public Player {
  public:
    Drow(std::pair<int, int> position);
    virtual void applyItem(std::shared_ptr<Potion> potion) override;
    virtual void attack(std::shared_ptr<Enemy> enemy) override;
    virtual void nextTurn() override;
};

#endif
