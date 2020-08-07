#ifndef _ORC_
#define _ORC_

#include "../enemy.h"

class Orc : public Enemy, std::enable_shared_from_this<Orc> {
    public:
        Orc(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
