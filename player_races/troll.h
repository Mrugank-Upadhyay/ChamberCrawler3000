#ifndef _TROLL_
#define _TROLL_

#include "../player.h"

class Troll: public Player, std::enable_shared_from_this<Troll> {
  public:
    Troll(std::pair<int, int> position);
    virtual void attack(std::shared_ptr<Enemy> enemy) override;
    virtual void nextTurn() override;
};

#endif
