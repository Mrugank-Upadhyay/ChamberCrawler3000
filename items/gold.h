#ifndef _GOLD_
#define _GOLD_

#include "../item.h"

class Player;

class Gold : public Item, std::enable_shared_from_this<Gold> {
    int amount;

    public:
        Gold(std::pair<int, int> position, int amount);
        int getAmount();
        virtual void apply(std::shared_ptr<Player> player) override;
};

#endif
