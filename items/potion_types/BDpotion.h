#ifndef _BDPOTION_
#define _BDPOTION_

#include "potion.h"

class BDPotion : public Potion {
    public:
        BDPotion(std::string rep, std::pair<int, int> position);
};

#endif
