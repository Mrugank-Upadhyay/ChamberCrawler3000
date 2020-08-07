#ifndef _DRAGON_
#define _DRAGON_

#include "../enemy.h"

class Dragon : public Enemy, std::enable_shared_from_this<Dragon> {
    public:
        Dragon(std::pair<int, int> position);
        virtual std::pair<int, int> move(int x, int y) override;
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
