#ifndef _POTION_
#define _POTION_

#include "item.h"

class Player;

class Potion : public Item {
    int health;
    int atk;
    int def;

    public:
        Potion(std::string type, std::string rep, std::pair<int, int> position);
        virtual void apply(Player p) override;
        virtual std::string printInfo();
};

#endif
