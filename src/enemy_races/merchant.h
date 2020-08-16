#ifndef _MERCHANT_
#define _MERCHANT_

#include "../enemy.h"

class Merchant : public Enemy {
    public:
        Merchant(std::pair<int, int> position);
        virtual std::string attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
