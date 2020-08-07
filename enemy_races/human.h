#ifndef _HUMAN_
#define _HUMAN_

#include "../enemy.h"

class Human : public Enemy, std::enable_shared_from_this<Human> {
    public:
        Human(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
