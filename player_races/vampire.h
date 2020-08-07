#ifndef _VAMPIRE_
#define _VAMPIRE_

#include "../player.h"

class Vampire : public Player {
    public:
        Vampire(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Enemy> enemy) override;
        virtual void nextTurn() override;
};

#endif
