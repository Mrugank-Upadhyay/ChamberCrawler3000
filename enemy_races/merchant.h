#ifndef _MERCHANT_
#define _MERCHANT_

#include "../enemy.h"

class Merchant : public Enemy {
    public:
        Merchant(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
};

#endif
