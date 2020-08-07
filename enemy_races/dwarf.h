#ifndef _DWARF_
#define _DWARF_

#include "../enemy.h"

class Dwarf : public Enemy, std::enable_shared_from_this<Dwarf> {
    public:
        Dwarf(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};

#endif