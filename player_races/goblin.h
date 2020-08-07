#ifndef _GOBLIN_
#define _GOBLIN_

#include "../player.h"

class Goblin: public Player {
  public:
    Goblin(std::pair<int, int> position);
    void attack(std::shared_ptr<Enemy> enemy) override;
    void getStruckBy(std::shared_ptr<Orc> enemy) override;
};

#endif
