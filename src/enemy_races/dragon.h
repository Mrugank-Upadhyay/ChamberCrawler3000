#ifndef _DRAGON_
#define _DRAGON_

#include "../enemy.h"

class Dragon : public Enemy {
      Cell * goldCell;
    public:
        Dragon(std::pair<int, int> position, Cell * goldCell = nullptr);

        Cell * getGoldCell();
        void setGoldCell(Cell * goldCell);

        virtual std::pair<int, int> move() override;
        virtual void attack(std::shared_ptr<Player> player) override;
};

#endif
