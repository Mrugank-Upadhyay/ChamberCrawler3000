#ifndef _DRAGON_
#define _DRAGON_

#include "../enemy.h"

class Dragon : public Enemy {
      std::shared_ptr<Cell> goldCell;
    public:
        Dragon(std::pair<int, int> position);

        std::shared_ptr<Cell> getGoldCell();
        void setGoldCell(std::shared_ptr<Cell> goldCell);

        virtual std::pair<int, int> move() override;
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
