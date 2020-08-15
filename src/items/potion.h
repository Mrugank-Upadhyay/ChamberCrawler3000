#ifndef _POTION_
#define _POTION_

#include "../item.h"

class Player;

class Potion : public Item {
    int hp;
    int atk;
    int def;

    public:
        Potion(std::string type, std::string rep, std::pair<int, int> position, int hp, int atk, int def);
        int getHP();
        int getATK();
        int getDEF();
        virtual void apply(std::shared_ptr<Player> player) override;
        virtual std::string info() override;
};

#endif
