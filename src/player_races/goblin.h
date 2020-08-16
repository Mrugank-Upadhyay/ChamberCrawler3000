#ifndef _GOBLIN_
#define _GOBLIN_

#include "../player.h"

class Goblin: public Player {
  public:
    Goblin(std::pair<int, int> position);
    virtual std::string attack(std::shared_ptr<Enemy> enemy) override;
    virtual std::string getStruckBy(Orc * enemy) override;
};

#endif
