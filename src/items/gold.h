#ifndef _GOLD_
#define _GOLD_

#include "../item.h"

class Player;

class Gold : public Item {
    int amount;
    bool canPickUp;

    public:
        Gold(std::pair<int, int> position, int amount);
        int getAmount();

        bool getCanPickUp();
        void setCanPickUp(bool canPickUp);

        virtual void apply(std::shared_ptr<Player> player) override;
        virtual std::string info() override;
};

#endif
