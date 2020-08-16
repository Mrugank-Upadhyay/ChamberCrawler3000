#ifndef _DWARF_
#define _DWARF_

#include "../enemy.h"

class Dwarf : public Enemy {
    public:
        Dwarf(std::pair<int, int> position);
        virtual std::string attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif
