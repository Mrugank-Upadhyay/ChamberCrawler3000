#ifndef _DROW_
#define _DROW_

#include "../player.h"

class Drow: public Player {
  public:
    Drow(std::pair<int, int> position);
    void applyItem(std::shared_ptr<Potion> potion) override;
    void attack(std::shared_ptr<Enemy> enemy) override;
};

#endif
