#ifndef _GOLD_
#define _GOLD_

#include "../item.h"

class Player;

class Gold : public Item {
    int amount;

    public:
        Gold(std::pair<int, int> position, int amount);
        void apply(Player p) override;
};

#endif
