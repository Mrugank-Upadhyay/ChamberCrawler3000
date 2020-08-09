#ifndef _POTION_
#define _POTION_

#include "../item.h"

class Player;

class Potion : public Item, std::enable_shared_from_this<Potion> {
    int hp;
    int atk;
    int def;

    public:
        Potion(std::string type, std::string rep, std::pair<int, int> position);
        int getHP();
        int getATK();
        int getDEF();
        virtual void apply(Player * player) override;
        virtual std::string printInfo();
};

#endif
