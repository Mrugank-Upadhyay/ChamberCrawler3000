#ifndef _DRAGON_
#define _DRAGON_

#include "../enemy.h"

class Dragon : public Enemy {
      Cell * goldCell;
    public:
        Dragon(std::pair<int, int> position, Cell * goldCell = nullptr);

        Cell * getGoldCell();
        void setGoldCell(Cell * goldCell);

        virtual void move() override;
        virtual std::string attack(std::shared_ptr<Player> player) override;
};

#endif
