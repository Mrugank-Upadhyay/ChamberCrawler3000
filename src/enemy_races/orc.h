#ifndef _ORC_
#define _ORC_

#include "../enemy.h"

class Orc : public Enemy {
    public:
        Orc(std::pair<int, int> position);
        virtual std::string attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
