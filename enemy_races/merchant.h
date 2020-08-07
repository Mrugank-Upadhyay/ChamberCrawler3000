#ifndef _MERCHANT_
#define _MERCHANT_

#include "../enemy.h"

class Merchant : public Enemy, std::enable_shared_from_this<Merchant> {
    public:
        Merchant(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
